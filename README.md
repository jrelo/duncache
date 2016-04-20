# duncache
recursively remove files in given directory from the linux filesystem pagecache using POSIX_FADV_DONTNEED and fts() functions for directory traversal.

based on answers given by sehe and tpar44 here: http://stackoverflow.com/questions/12609747/traversing-a-filesystem-with-fts3.

[quote]The fts_children() function returns a pointer to an FTSENT structure describing the first entry in a NULL terminated linked list of files in the directory, if successful. The fts_children() function may fail and set errno for any of the errors that the chdir(), malloc(), opendir(), readdir(), and stat() functions specify.[/quote]
