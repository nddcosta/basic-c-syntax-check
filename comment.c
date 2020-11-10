#include "comment.h"



void update_comment_status(char c, struct Status *status){
	if(status->comment->in_multi_line){
		update_multi_line_comment(c, status);
	}else if(status->comment->in_single_line){
		update_single_line_comment(c, status);
	}
}

void update_multi_line_comment(char c, struct Status *status){
	if(status->comment->checking_for_comment_end){
		status->comment->checking_for_comment_end = 0;
		if(c == '/'){
			status->comment->in_multi_line = 0;
		}
	}else{
		if(c == '*'){
			status->comment->checking_for_comment_end = 1;
		}
	}
}

void update_single_line_comment(char c, struct Status *status){
	if(c == '\n'){
		status->comment->in_single_line = 0;
	}
}

int is_comment_char(char c){
	return (c == '/' || c == '*');
}

void update_comment_type(char c, struct Status *status){
	if(status->comment->checking_for_comment_start){
		if(c == '*'){
			status->comment->checking_for_comment_start = 0;
			status->comment->in_multi_line = 1;
		}else if(c == '/'){
			status->comment->checking_for_comment_start = 0;
			status->comment->in_single_line = 1;
		}
	}else{
		if(c == '/'){
			status->comment->checking_for_comment_start = 1;
		}
	}
}

int in_comment(struct Status *status){
	return status->comment->in_multi_line || status->comment->in_single_line;
}
