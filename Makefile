.PHONY: clean All

All:
	@echo "----------Building project:[ CsoProject - Debug ]----------"
	@cd "CsoProject" && "$(MAKE)" -f  "CsoProject.mk"
clean:
	@echo "----------Cleaning project:[ CsoProject - Debug ]----------"
	@cd "CsoProject" && "$(MAKE)" -f  "CsoProject.mk" clean
