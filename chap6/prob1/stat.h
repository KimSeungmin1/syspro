struct stat {
	mode_t st_mode;
	ino_t st_ino;
	dev_t st_dev;
	dev_t st_rdev;
	nlink_t st_nlink;
	uid_t st_uid;
	gid_t st_gid;
	off_t st_size;
	time_t st_atime;
	time_t st_mtime;
	time_t st_ctime;
	long st_blksize;
	long st_blocks;
};
