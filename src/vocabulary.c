typedef struct vocab {
	str* numbers;
	tab* bi_ops;
	tab* keywords;
} vocab;

vocab* initVocab() {
	vocab* v = malloc(sizeof(vocab));

	//numbers
	v->numbers = s("0123456789");

	//bi-ops
	v->bi_ops = Tab__new(11ULL, NULL);
	tab_str__indexAssign(v->bi_ops,  0ULL, s("=="));
	tab_str__indexAssign(v->bi_ops,  1ULL, s("!="));
	tab_str__indexAssign(v->bi_ops,  2ULL, s("<="));
	tab_str__indexAssign(v->bi_ops,  3ULL, s(">="));
	tab_str__indexAssign(v->bi_ops,  4ULL, s("->"));
	tab_str__indexAssign(v->bi_ops,  5ULL, s("++"));
	tab_str__indexAssign(v->bi_ops,  6ULL, s("--"));
	tab_str__indexAssign(v->bi_ops,  7ULL, s("&&"));
	tab_str__indexAssign(v->bi_ops,  8ULL, s("||"));
	tab_str__indexAssign(v->bi_ops,  9ULL, s("<<"));
	tab_str__indexAssign(v->bi_ops, 10ULL, s(">>"));

	//keywords
	v->keywords = Tab__new(27ULL, NULL);
	tab_str__indexAssign(v->keywords  0ULL, s("ret"));
	tab_str__indexAssign(v->keywords  1ULL, s("if_"));
	tab_str__indexAssign(v->keywords  2ULL, s("els"));
	tab_str__indexAssign(v->keywords  3ULL, s("for"));
	tab_str__indexAssign(v->keywords  4ULL, s("whi"));
	tab_str__indexAssign(v->keywords  5ULL, s("int"));
	tab_str__indexAssign(v->keywords  6ULL, s("szo"));
	tab_str__indexAssign(v->keywords  7ULL, s("byt"));
	tab_str__indexAssign(v->keywords  8ULL, s("stc"));
	tab_str__indexAssign(v->keywords  9ULL, s("shr"));
	tab_str__indexAssign(v->keywords 10ULL, s("lng"));
	tab_str__indexAssign(v->keywords 11ULL, s("voi"));
	tab_str__indexAssign(v->keywords 12ULL, s("tdf"));
	tab_str__indexAssign(v->keywords 13ULL, s("enm"));
	tab_str__indexAssign(v->keywords 14ULL, s("stt"));
	tab_str__indexAssign(v->keywords 15ULL, s("brk"));
	tab_str__indexAssign(v->keywords 16ULL, s("ctn"));
	tab_str__indexAssign(v->keywords 17ULL, s("swi"));
	tab_str__indexAssign(v->keywords 18ULL, s("cas"));
	tab_str__indexAssign(v->keywords 19ULL, s("def"));
	tab_str__indexAssign(v->keywords 20ULL, s("ext"));
	tab_str__indexAssign(v->keywords 21ULL, s("do_"));
	tab_str__indexAssign(v->keywords 22ULL, s("sgn"));
	tab_str__indexAssign(v->keywords 23ULL, s("usg"));
	tab_str__indexAssign(v->keywords 24ULL, s("cst"));
	tab_str__indexAssign(v->keywords 25ULL, s("flt"));
	tab_str__indexAssign(v->keywords 26ULL, s("dbl"));

	//return result
	return v;
}
