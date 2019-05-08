.DEFAULT_GOAL = devall
.DEFAULT:
	@$(MAKE) -fdep/über.mk/makefile $@

test: devall
	$(shell find bin/test -type f)
