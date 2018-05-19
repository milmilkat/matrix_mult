## Parallel Matrix Multiplication Project

This project is a prototype for a simple application running a parallel multiplication
of given 2 matrices described within plain text files.

Two sample text files are provided within `input` directory which is:
- matrix_a
- matrix_b

Both files have the following content:

```
2 2
1 1 0.3
1 2 0.1
2 2 1.3
```

### Running this project with default parameters

To run this project using provided matrices described on `matrix_a` and `matrix_b` files,
just run `make` within the root project's directory. It will compile this project,
and will run the matrix multiplication which results will be provided within
`output/matrix_c` file.

### Generating random matrix

Sometimes we need a large matrix representation within a file to do some tests with `matrix_mult` project.
Instead of manually writing it, just run `make` and then run `./bin/genmatrix <number_of_rows> <number_of_cols>`.
It will generate a matrix with random values (double precision) with the format required by `matrix_mult` project.

### Testing

To run some unit tests, just type `make test`


### Benchmark

We have created a simple benchmark that compares pthreads against openMP implementation.
Type `make bench` to see some results.

### Parallelization

The idea is to parallelize function `matrix_mult` described at `matrix.c` and
`matrix.h` source files.

### Contributing

To contribute to this project, just create a fork of this project on GitHub and
to send your contribution, push a new branch and create a [Pull Request](https://help.github.com/articles/about-pull-requests/) based on this new branch.
By sending a Pull Request, each contributor can discuss the source code together and merge on master
when they come to a common solution/idea.

### Authors

This project is maintained by Adolfo Eloy and Milad Katebi and was created at IME-USP.
