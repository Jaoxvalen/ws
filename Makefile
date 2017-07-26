.PHONY: clean All

All:
	@echo "----------Building project:[ ParallelSort - Debug ]----------"
	@cd "ParallelSort" && "$(MAKE)" -f  "ParallelSort.mk"
clean:
	@echo "----------Cleaning project:[ ParallelSort - Debug ]----------"
	@cd "ParallelSort" && "$(MAKE)" -f  "ParallelSort.mk" clean
