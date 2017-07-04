.PHONY: clean All

All:
	@echo "----------Building project:[ Matematica - Debug ]----------"
	@cd "Matematica" && "$(MAKE)" -f  "Matematica.mk"
clean:
	@echo "----------Cleaning project:[ Matematica - Debug ]----------"
	@cd "Matematica" && "$(MAKE)" -f  "Matematica.mk" clean
