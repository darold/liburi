/* Author: Mo McRoberts <mo.mcroberts@bbc.co.uk>
 *
 * Copyright 2015-2017 BBC
 */

/*
 * Copyright 2012 Mo McRoberts.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "p_liburi.h"

/* 'fragment' property accessors */

size_t
uri_fragment(const URI *restrict uri, char *restrict buf, size_t buflen)
{
	if(!uri->fragment)
	{
		if(buf && buflen)
		{
			*buf = 0;
		}
		return 0;
	}
	if(buf && buflen)
	{
		strncpy(buf, uri->fragment, buflen - 1);
		buf[buflen - 1] = 0;
	}
	return strlen(uri->fragment) + 1;
}

/* Return the fragment as const string pointer */
const char *
uri_fragment_str(const URI *uri)
{
	return uri->fragment;
}

/* Return the fragment as a newly-allocated string (which must be freed by
 * the caller)
 */
char *
uri_fragment_stralloc(const URI *uri)
{
	if(!uri->fragment)
	{
		errno = 0;
		return NULL;
	}
	return strdup(uri->fragment);
}

/* Set a new fragment (or remove it if newfragment is NULL) */
int
uri_set_fragment(URI *restrict uri, const char *restrict newfragment)
{
	char *sbuf;
	
	sbuf = NULL;
	if(newfragment)
	{
		sbuf = strdup(newfragment);
		if(!sbuf)
		{
			return -1;
		}
		newfragment = sbuf;
	}
	free(uri->fragment);
	uri->fragment = sbuf;
	uri->uri.fragment.first = sbuf;
	if(sbuf)
	{
		uri->uri.fragment.afterLast = strchr(sbuf, 0);
	}
	else
	{
		uri->uri.fragment.afterLast = NULL;
	}
	return 0;
}
