.PHONY: clean All

All:
	@echo "----------Building project:[ Algoritmo2 - Debug ]----------"
	@cd "Algoritmo2" && "$(MAKE)" -f  "Algoritmo2.mk"
clean:
	@echo "----------Cleaning project:[ Algoritmo2 - Debug ]----------"
	@cd "Algoritmo2" && "$(MAKE)" -f  "Algoritmo2.mk" clean
