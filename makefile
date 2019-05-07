.DEFAULT_GOAL = devall
.DEFAULT:
	@$(MAKE) -fdep/über.mk/makefile $@
