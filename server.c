#include "include.h"
#include "er_proc.h"

int main() {
    int server = Socket(AF_INET, SOCK_STREAM, 0);

    // Инициализируем все поля нулями
    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(7777);
    addr.sin_addr.s_addr = INADDR_ANY;

    Bind(server, (struct sockaddr *) &addr, sizeof addr);
    // В очереди может ожидать вплоть до 5 клиентов
    Listen(server, 5);

    socklen_t addrlen = sizeof addr;
    // Возвращает новый файловый дескриптор сокета для использования
    // с одним подключением.
    // Addr - указатель на структуру sockaddr, куда будет записан адрес
    // удаленного узла, запросившего соединение. Структура sockaddr в
    // этом параметре не требует инициализации и не управляет приемом соединения.
    // Она просто используется для сохранения адреса принятого соединения.
    int fd = Accept(server, (struct sockaddr *) &addr, &addrlen);

    char buf[256];
    ssize_t nread = read(fd, buf, 256);
    if (nread == -1) {
        perror("read failed");
        exit(1);
    }
    else if (nread == 0) {
        printf("EOF occured\n");
    }

    write(1, buf, nread);
    write(fd, buf, nread);

    close(fd);
    close(server);

    return 0;
}