FROM gcc:4.9
COPY . /usr/src/myapp
WORKDIR /usr/src/myapp
RUN gcc -c *.c -Wall && gcc -o myapp *.o
CMD ["./myapp"]