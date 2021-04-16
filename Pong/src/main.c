#include "application.h"

int main(void)
{
	Application *app = application_create("Pong", 800, 600);
	assert(app != NULL);

	application_run(app);
	application_free(app);

	return 0;
}