.PHONY: clean All

All:
	@echo "----------Building project:[ Sorting - Release ]----------"
	@cd "Sorting" && "$(MAKE)" -f  "Sorting.mk"
clean:
	@echo "----------Cleaning project:[ Sorting - Release ]----------"
	@cd "Sorting" && "$(MAKE)" -f  "Sorting.mk" clean
