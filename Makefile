.PHONY: clean All

All:
	@echo "----------Building project:[ ArenaTopCoder - Debug ]----------"
	@cd "ArenaTopCoder" && "$(MAKE)" -f  "ArenaTopCoder.mk"
clean:
	@echo "----------Cleaning project:[ ArenaTopCoder - Debug ]----------"
	@cd "ArenaTopCoder" && "$(MAKE)" -f  "ArenaTopCoder.mk" clean
