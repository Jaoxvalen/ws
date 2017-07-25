.PHONY: clean All

All:
	@echo "----------Building project:[ GraphPath - Debug ]----------"
	@cd "GraphPath" && "$(MAKE)" -f  "GraphPath.mk"
clean:
	@echo "----------Cleaning project:[ GraphPath - Debug ]----------"
	@cd "GraphPath" && "$(MAKE)" -f  "GraphPath.mk" clean
