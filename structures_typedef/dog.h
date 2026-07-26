#ifndef _Dog_Struct_H_
#define _Dog_Struct_H_

/**
 * struct dog - key data for dog
 * @name: name of dog
 * @age: age of dog
 * @owner: owner of dog
 *
 */
struct dog
{
	char *name;
	float age;
	char *owner;
};

/**
 * dog_t - Typedef for struct dog
 */
typedef struct dog dog_t;

void init_dog(struct dog *d, char *name, float age, char *owner);
void print_dog(struct dog *d);
dog_t *new_dog(char *name, float age, char *owner);
void free_dog(dog_t *d);

#endif /* _SAMPLE_HEADER_H_ */
