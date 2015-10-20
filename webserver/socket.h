#ifndef __SOCKET_H__
#define __SOCKET_H__
enum http_method{
  HTTP_GET,
  HTTP_UNSUPPORTED,
};

typedef struct{
  enum http_method method;
  int major_version;
  int minor_version;
  char *url;
} http_request;


/** Crée une socket serveur qui écoute sur toute les interfaces IPv4
    de la machine sur le port passé en paramètre. La socket retournée
    doit pouvoir être utilisée directement par un appel à accept.
    La fonction retourne -1 en cas d’erreur ou le descripteur de la
    socket créée. */
int creer_serveur(int port);
void initialiser_signaux(void);
void traitement_signal(int sig);
void skip_headers(FILE *client);
char *fgets_or_exit(char *buffer, int size, FILE *stream);
int parse_http_request(const char *request_line, http_request *request);
void send_status(FILE *client, int code, const char *reason_phrase);
void send_response(FILE *client, int code, const char *reason_phrase, const char * message_body);
char *rewrite_url(char *url);
int check_and_open(const char *url, const char *document_root);
int get_file_size(int fd);
int copy(int in, int out);


#endif
