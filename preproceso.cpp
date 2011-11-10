#include <iostream>
#include <fstream>

#include <iomanip>
using namespace std;

int main(int argc, char *argv[]) {
	ifstream train_image("train-images.idx3-ubyte", ios::in | ios::binary);
	ifstream train_label("train-labels.idx1-ubyte", ios::in | ios::binary);
	ofstream salida("preproceso.txt", ios::out);
	char * buffer_image;
	char * buffer_label;
	long length_image,length_label;
	
	if (train_image.is_open() && train_label.is_open())
	{
		//IMAGE
		// get length of file:
		train_image.seekg (0, ios::end);
		length_image = train_image.tellg();
		train_image.seekg (0, ios::beg);
		
		// allocate memory:
		buffer_image = new char [length_image];
		
		// read data as a block:
		train_image.read (buffer_image,length_image);
		
		//LABEL
		// get length of file:
		train_label.seekg (0, ios::end);
		length_label = train_label.tellg();
		train_label.seekg (0, ios::beg);
		
		// allocate memory:
		buffer_label = new char [length_label];
		
		// read data as a block:
		train_label.read (buffer_label,length_label);

		long inicio_image=16, inicio_label=8;
		long digito;
		
		salida << 60000<<endl;
		
		for(int K=0;K<60000;K++){
			
			//digito imagen
			int prendido=0;
			int cuad1=0,cuad2=0,cuad3=0,cuad4=0;
			for(int L=0;L<784;L++){
				prendido = (buffer_image[inicio_image+L] > 100) ? 1 : 0;
				if(L%28<14 && L/28<14){
					cuad2 += prendido;
				}
				
				if(L%28<14 && L/28>=14){
					cuad3 += prendido;
				}
				
				if(L%28>=14 && L/28<14){
					cuad1 += prendido;
				}
				
				if(L%28>=14 && L/28>=14){
					cuad4 += prendido;
				}
				
			}
			salida<<cuad1<<" "<<cuad2<<" "<<cuad3<<" "<<cuad4<<" ";
			inicio_image = inicio_image+784;
			
			
			
			digito = (int) buffer_label[inicio_label+K];
			
			for(int P=0;P<9;P++){
				if(P==digito)
					salida<<1<<" ";
				else
					salida<<-1<<" ";
			}
			if(9==digito)
				salida<<1<<endl;
			else
				salida<<-1<<endl;
		}
	}
	else
		{
			cout << "Error opening file";
		}
	
	return 0;
}
