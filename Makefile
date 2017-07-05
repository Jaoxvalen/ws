.PHONY: clean All

All:
	@echo "----------Building project:[ Sorting - Debug ]----------"
	@cd "Sorting" && "$(MAKE)" -f  "Sorting.mk"
clean:
	@echo "----------Cleaning project:[ Sorting - Debug ]----------"
	@cd "Sorting" && "$(MAKE)" -f  "Sorting.mk" clean
