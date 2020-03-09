#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"
#include "luamath.h"

#define EOFMARK	   "<eof>"
#define EOFMARKLEN (sizeof(EOFMARK) / sizeof(char) - 1)

int print_stack(lua_State* L)
{
	int n = lua_gettop(L);
	if (n > 0)
	{ /* any result to be printed? */
		luaL_checkstack(L, LUA_MINSTACK, "too many results to print");
		lua_getglobal(L, "print");
		lua_insert(L, 1);
		lua_pcall(L, n, 0, 0);
	}
	/*while (lua_gettop(L))
	{
		int type = lua_type(L, -1);
		switch (type)
		{
		case LUA_TNUMBER:
			printf("%d\n", lua_tonumber(L, -1));
			break;
			case LUA_TBOOLEAN:
			puts(lua_toboolean(L, -1) ? "true" : "false");
			break;
			case LUA_TSTRING:
			printf("%s\n", lua_tostring(L, -1));
			break;

		default:
			break;
		}
		lua_pop(L, 1);
	}*/
}

int msghandler(lua_State* L)
{
	while (lua_gettop(L))
	{
		if (lua_isnumber(L, -1))
		{
			printf("msg : %d\n", lua_tonumber(L, -1));
		}
		else
		{
			printf("msg : %s\n", lua_tostring(L, -1));
		}

		lua_pop(L, 1);
	}
	return 0;
}

// Check if statement was incomplete
int statement_incomplete(lua_State* L, int result)
{

	if (result == LUA_ERRSYNTAX)
	{
		size_t lmsg = 0;
		const char* msg = lua_tolstring(L, -1, &lmsg);
		if (lmsg >= EOFMARKLEN && strcmp(msg + lmsg - EOFMARKLEN, EOFMARK) == 0)
		{
			lua_pop(L, 1);
			return 1;
		}
	}
	return 0;
}

#define PROMPT1 "> "
#define PROMPT2 ">> "

void readline(lua_State* L)
{
	size_t lbuf = 0;
	size_t bufpos = 0;
	char* buf = NULL;
	buf = malloc(256);
	lbuf = 256;

	for (size_t i = 0;; i++) // Repeat until user entered complete statement
	{
		// Get line from stdin
		if (i > 0)
			fputs(PROMPT2, stdout);
		else
		{
			fputs(PROMPT1, stdout);
		}

		int c;
		while ((c = fgetc(stdin)) != '\n')
		{
			if (bufpos >= lbuf)
				buf = realloc(buf, (lbuf *= 2));
			buf[bufpos++] = c;
		}

		buf[bufpos] = '\0';
		int result = luaL_loadbuffer(L, buf, strlen(buf), "line");

		lua_pcall(L, 0, 0, 0);
		print_stack(L);
		if (result != LUA_OK)
		{
			// Other error
			if (statement_incomplete(L, result) == 0)
			{
				free(buf);
				return;
			}
			// Add new line and continue the statement
			if (bufpos + 2 > lbuf)
				buf = realloc(buf, (lbuf *= 2));
			buf[bufpos++] = '\n';
			buf[bufpos] = '\0';
		}
		// Success
		else
		{

			return;
		}
	}
}

int main(void)
{
	char buff[256];
	lua_State* L = luaL_newstate(); /* opens Lua */
	luaL_openlibs(L);

	luamath_load(L);

	for (;;)
	{
		readline(L);
	}

	lua_close(L);
	return 0;
}
