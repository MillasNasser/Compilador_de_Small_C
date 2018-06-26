int main(){
	int mult = 1, fat;
	read fat;
	int backup = fat;

	while(backup > 0){
		print(backup);
		backup = backup - 1;
	}

	if(fat > 10){
		fat = 10;
	}

	int i;
	for(i = 1; i <= fat; i = i+1){
		mult = mult * i;
	}
	print(mult);
}