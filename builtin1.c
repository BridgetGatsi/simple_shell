#include "shell.h"

/**
 * add_key - create a new environment variable
 * @vars: pointer to struct of variables
 * Return: void
 */
void add_key(vars_t *vars)
{
unsigned int k;
char **newenv;

for (k = 0; vars->env[k] != NULL; k++)
;
newenv = malloc(sizeof(char *) * (k + 2));
if (newenv == NULL)
{
print_error(vars, NULL);
vars->status = 127;
new_exit(vars);
}
for (k = 0; vars->env[k] != NULL; k++)
newenv[k] = vars->env[k];
newenv[k] = add_value(vars->av[1], vars->av[2]);
if (newenv[k] == NULL)
{
print_error(vars, NULL);
free(vars->buffer);
free(vars->commands);
free(vars->av);
free_env(vars->env);
free(newenv);
exit(127);
}
newenv[k + 1] = NULL;
free(vars->env);
vars->env = newenv;
}

/**
 * find_key:finds an environment variable
 * @key: environment variable to find
 * @env: array of environment variables
 * Return: pointer to address of the environment variable
 */
char **find_key(char **env, char *key)
{
unsigned int k, j, len;

len = _strlen(key);
for (k = 0; env[i] != NULL; k++)
{
for (j = 0; j < len; j++)
if (key[j] != env[k][j])
break;
if (j == len && env[k][j] == '=')
return (&env[k]);
}
return (NULL);
}

/**
 * add_value - create a new environment variable string
 * @key: variable name
 * @value: variable value
 *
 * Return: pointer to the new string;
 */
char *add_value(char *key, char *value)
{
unsigned int len1, len2, k, j;
char *new;

len1 = _strlen(key);
len2 = _strlen(value);
new = malloc(sizeof(char) * (len1 + len2 + 2));
if (new == NULL)
return (NULL);
for (k = 0; key[k] != '\0'; k++)
new[k] = key[k];
new[k] = '=';
for (j = 0; value[j] != '\0'; j++)
new[k + 1 + j] = value[j];
new[k + 1 + j] = '\0';
return (new);
}

/**
 * _atoi - converts a string into an integer
 * @str: string to convert
 *
 * Return: the integer value, or -1 if an error occurs
 */
int _atoi(char *str)
{
unsigned int k, digits;
int num = 0, num_test;

num_test = INT_MAX;
for (digits = 0; num_test != 0; digits++)
num_test /= 10;
for (k = 0; str[k] != '\0' && k < digits; k++)
{
num *= 10;
if (str[k] < '0' || str[k] > '9')
return (-1);
if ((k == digits - 1) && (str[k] - '0' > INT_MAX % 10))
return (-1);
num += str[k] - '0';
if ((k == digits - 2) && (str[k + 1] != '\0') && (num > INT_MAX / 10))
return (-1);
}
if (k > digits)
return (-1);
return (num);