struct vfsblock
{
	int blockno;
	char type;
	char inodecount;
	int inodestartno;
	char inodesize = 16;
	char maxinodecount=(512/inodesize)-1;
	inode node[maxinodecount];
};
struct inode
{
	int no;
	int datablock;
	int a;
	int b;
}