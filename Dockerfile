FROM gcc:4.9
COPY . /usr/src/myapp
WORKDIR /usr/src/myapp
RUN gcc -c *.c && gcc -o myapp *.o
CMD ["./myapp"]