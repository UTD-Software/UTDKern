//Fills pntr with n 0s
void bzero(void *pntr,int n){
	int i;
	for(i = 0; i < n;i++)
		*((char*)pntr + i) = 0;
}
