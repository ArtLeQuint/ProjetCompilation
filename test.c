int main() 
{
	int i;
	int j;
	int height = 128 ;
	int width = 128; 
	for (i = 1; i < height - 1; i++) 
	{ 
		printi(i);

		for (j = 1; j < width - 1; j++) 
		{ 
			printi(j); 
		}
	 }
	return 0;
}
