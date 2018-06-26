int main(){
	int mult = 1, fat = 2;
	int backup = fat * 3 / mult;

	while(backup > 0){
		print(backup);
		if(mult != fat){
			print(mult);
		}
		backup = backup - 1;
	}

	if(fat > 10){
		fat = 10;
	}else{
		fat = 3;
		fat = 10;
	}

	read fat;
	int i;
	for(i = 1; i <= fat; i = i+1){
		mult = mult * i;
	}
	print(mult);
}