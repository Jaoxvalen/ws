.PHONY: clean All

All:
	@echo "----------Building project:[ Parallel - Debug ]----------"
	@cd "Paralell" && "$(MAKE)" -f  "Parallel.mk"
clean:
	@echo "----------Cleaning project:[ Parallel - Debug ]----------"
	@cd "Paralell" && "$(MAKE)" -f  "Parallel.mk" clean
