#include <glob.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "index_lib.h"

char *input_prompt(char *prompt, char *buf, size_t len, FILE *stream) {
  printf("%s", prompt);
  return fgets(buf, len, stream);
}

void print_result_list(ll_string *resultlist,
                       MetadataLookupTable *message_id_to_metadata) {
  int i = 1;
  for (ll_string *here = resultlist; here; here = here->next, i++) {
    PostMetadata *metadata =
        metadata_lookup(message_id_to_metadata, here->value);
    printf("  - %d %s -> %s\n", i, metadata->newsgroups, metadata->subject);
  }
}

void print_file(char *filename) {
  printf("\n"
         "========================================"
         "========================================\n");
  FILE *infile = fopen(filename, "r");
  char buf[1024];
  while (fgets(buf, 1024, infile)) {
    chomp(buf);
    printf("%s\n", buf);
  }
  fclose(infile);
}

string_set *load_stopwords(char *filename) {
  string_set *out = make_empty_set();
  FILE *infile = fopen(filename, "r");
  char buf[1024];
  while (fgets(buf, 1024, infile)) {
    chomp(buf);
    out = add(out, buf);
  }
  fclose(infile);
  return out;
}

int main(void) {
  glob_t globbuf;
  glob("20_newsgroups/*/*", 0, NULL, &globbuf);

  MetadataLookupTable *message_id_to_metadata =
      build_metadata_lookup_table(10000);
  TermLookupTable *terms_to_message_ids = build_term_lookup_table(10000);

  string_set *stopwords = load_stopwords("english_stopwords");

  for (size_t i = 0; i < globbuf.gl_pathc; i++) {
    printf("indexing: %s\n", globbuf.gl_pathv[i]);
    PostMetadata *metadata = extract_metadata(globbuf.gl_pathv[i]);

    if (!metadata_lookup(message_id_to_metadata, metadata->message_id)) {
      store_metadata(message_id_to_metadata, metadata);
    }

    ll_string *terms = extract_terms(globbuf.gl_pathv[i], stopwords);
    if (terms) {
      for (ll_string *term = terms; term; term = term->next) {
        add_message_id_to_term(terms_to_message_ids, term->value,
                               metadata->message_id);
      }
    }
    free_post_metadata(metadata);
    free_list(terms);
  }
  globfree(&globbuf);
  printf("indexing complete!!\n");

  // main interaction loop
  bool done = false;
  char cmdbuf[140];
  ll_string *resultlist = NULL;

  while (!done &&
         input_prompt("search command (help for help)> ", cmdbuf, 140, stdin)) {
    chomp(cmdbuf);
    lowercase(cmdbuf);
    if (!strcmp(cmdbuf, "")) {
      continue;
    }

    ll_string *cmdtokens = tokenize_string(cmdbuf);
    if (!cmdtokens) {
      continue;
    }
    char *cmd = cmdtokens->value;
    if (!strcmp(cmd, "quit")) {
      done = true;
    } else if (!strcmp(cmd, "help")) {
      printf("possible commands are...\n"
             "- quit\n"
             "- help\n"
             "- or <query>\n"
             "- and <query>\n"
             "- show <resultnum>\n");
    } else if (!strcmp(cmd, "and")) {
      printf("doing AND query\n");
      string_set *result =
          intersection_lookup(terms_to_message_ids, cmdtokens->next);
      free_list(resultlist);
      resultlist = list_entries(result);
      print_result_list(resultlist, message_id_to_metadata);
      free_set(result);
    } else if (!strcmp(cmd, "or")) {
      printf("doing OR query\n");
      string_set *result = union_lookup(terms_to_message_ids, cmdtokens->next);

      free_list(resultlist);
      resultlist = list_entries(result);
      print_result_list(resultlist, message_id_to_metadata);
      free_set(result);
    } else if (!strcmp(cmd, "show")) {
      bool show_success = false;
      if (cmdtokens->next) {
        int resultnum = atoi(cmdtokens->next->value) - 1;
        ll_string *here = get_element(resultlist, resultnum);
        if (here) {
          char *message_id = here->value;
          PostMetadata *metadata =
              metadata_lookup(message_id_to_metadata, message_id);
          print_file(metadata->filename);
          show_success = true;
        }
      }

      if (!show_success) {
        printf("need a result number from the most recent results list\n");
      }
    } else {
      printf("unknown command\n");
    }
    free_list(cmdtokens);
  }

  free_list(resultlist);
  free_set(stopwords);
  free_term_lookup_table(terms_to_message_ids);
  free_metadata_lookup_table(message_id_to_metadata);

  printf("\nok bye!\n");

  return 0;
}
