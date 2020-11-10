
#ifndef STATUS_H
#define STATUS_H

#include "symbol.h"
#include "comment.h"
#include "quote.h"

struct Status{	
	struct Symbol *symbol;
	struct Comment *comment;
	struct Quote *quote;
};

#endif
