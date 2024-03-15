#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#if defined __USE_MISC || defined __USE_BSD || defined __USE_XOPEN_EXTENDED
extern int mknod (const char *__path, __mode_t __mode, __dev_t __dev)
__THROW __nonnull ((1));
#endif

const int BUFFER_SIZE = 128;

ssize_t read_from_file(char* path, char* dest, int size){
    int fd;
    if((fd = open(path, O_RDONLY)) < 0){
        printf("Can\'t open file\n");
        exit(-1);
    }
    ssize_t read_bytes = read(fd, dest, size);
    if(read_bytes == -1){
        printf("Can\'t read from the file\n");
        exit(-1);
    }
    dest[read_bytes] = '\0';
    if(close(fd) < 0){
        printf("Can\'t close file\n");
        exit(-1);
    }
    return read_bytes;
}

ssize_t write_to_file(char* path,char* buffer, size_t size){
    int fdWrite;
    if((fdWrite = open(path, O_WRONLY | O_CREAT, 0666)) < 0){
        printf("Can't open file for writing!\n");
        exit(-1);
    }

    ssize_t written = write(fdWrite, buffer, size);
    if(written != size){
        printf("Can't write all string!\n");
        exit(-1);
    }

    if(close(fdWrite) < 0){
        printf("Can\'t close file\n");
        exit(-1);
    }
    return written;
}

int main(int argc, char** argv){
    if(argc != 3){
        printf("execute programm with three param: './prog.out input.txt output.txt'\n");
        return 0;
    }

    // files' paths for reading and writing
    char* input_path = argv[1];
    char* output_path = argv[2];

    char read_buffer[BUFFER_SIZE + 1];

    const char* fifo_read = "first_pipe.fifo";
    const char* fifo_write = "second_pipe.fifo";
    int fifo_fd, input_fd, output_fd;
    ssize_t read_bytes;

    mknod(fifo_read, S_IFIFO | 0666, 0);
    mknod(fifo_write, S_IFIFO | 0666, 0);
    // descriptors for file and FIFO
    if((fifo_fd = open(fifo_read, O_WRONLY)) < 0){
        printf("Can\'t open FIFO for writting\n");
        exit(-1);
    }
    if((input_fd = open(input_path, O_RDONLY)) < 0){
        printf("Can\'t open file\n");
        exit(-1);
    }
    if((output_fd = open(output_path, O_WRONLY | O_CREAT, 0666)) < 0){
        printf("Can't open file for writing!\n");
        exit(-1);
    }

    do {
        read_bytes = read(input_fd, read_buffer, BUFFER_SIZE);
        if(read_bytes == -1) {
            printf("Can\'t write this file\n");
            exit(-1);
        }
        read_buffer[read_bytes] = '\0';
        size_t written = write(fifo_fd, read_buffer, read_bytes);
        if(written != read_bytes){
            printf("Can\'t write all string to FIFO\n");
            exit(-1);
        }
        // write(1, read_buffer, read_bytes);
    } while(read_bytes == BUFFER_SIZE);

    if(close(fifo_fd) < 0) {
        printf("reader: Can\'t close FIFO\n");
        exit(-1);
    }

    if(close(input_fd) < 0) {
        printf("Can\'t close file\n");
    }

    if((fifo_fd = open(fifo_write, O_RDWR)) < 0){
        printf("Can\'t open FIFO for reading\n");
        exit(-1);
    }

    char write_buffer[BUFFER_SIZE + 1];
    do {
        read_bytes = read(fifo_fd, write_buffer, BUFFER_SIZE);
        if(read_bytes <= 0){
            printf("Can\'t read string from FIFO\n");
            exit(-1);
        }
        write_buffer[read_bytes] = '\0';
        ssize_t written = write(output_fd, write_buffer, read_bytes);
        if(written != read_bytes){
            printf("Can't write all string!\n");
            exit(-1);
        }
        printf("%s\n", write_buffer);
    } while (read_bytes == BUFFER_SIZE);

    if(close(fifo_fd) < 0){
        printf("Can\'t close FIFO");
        exit(-1);
    }
    if(close(output_fd) < 0){
        printf("Can\'t close file for writing");
        exit(-1);
    }
}
