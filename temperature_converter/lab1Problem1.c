// Henry Ngo 
// CLA1
// This program will convert temperatures in fahrenheit, celsius, or kelvin

#include <stdio.h> 

int main(){
    char starting_temperature, target_temperature; 
    float user_temperature, kelvin, celsius, fahrenheit; 
  
    printf("Enter starting temperature scale (F/C/K): "); 
    scanf("%c", &starting_temperature);
    printf("Enter target temperature scale (F/C/K): "); 
    scanf("\n%c", &target_temperature);
    printf("Enter temperature value: "); 
    scanf("\n%f", &user_temperature);

    if (starting_temperature == 'C' || starting_temperature == 'c'){
      if(target_temperature == 'K' || target_temperature == 'k'){
        kelvin = user_temperature + 273.15; 
        printf("%0.2fC is equivalent to %0.2fK\n", user_temperature, kelvin);
      } else if(target_temperature == 'F' || target_temperature == 'f'){
          fahrenheit = (user_temperature)*(9.0/5.0) + 32;  
          printf("%0.2fC is equivalent to %0.2fF\n", user_temperature, fahrenheit);
      }
    }
    if (starting_temperature == 'F' || starting_temperature == 'f'){
      if(target_temperature == 'K' || target_temperature == 'k'){
        kelvin = (user_temperature - 32) * (5.0/9.0) + 273.15; 
        printf("%0.2fF is equivalent to %0.2fK\n", user_temperature, kelvin);
      } else if(target_temperature == 'C' || target_temperature == 'c'){
        celsius = (user_temperature-32) * (5.0/9.0);
        printf("%0.2fF is equivalent to %0.2fC\n", user_temperature, celsius); 

      }
    }
  if (starting_temperature == 'K' || starting_temperature == 'k'){
    if(target_temperature == 'C' || target_temperature == 'c'){
      celsius = user_temperature - 273.15; 
      printf("%0.2fK is equivalent to %0.2fC\n", user_temperature, celsius);
    } 
    else if(target_temperature == 'F' || target_temperature == 'f'){
      fahrenheit = (user_temperature-273.15)*(9.0/5.0) + 32;
      printf("%0.2fK is equivalent to %0.2fF\n", user_temperature, fahrenheit); 

    }
  }
}
