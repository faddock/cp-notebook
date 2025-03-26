# Compiler and flags
CXX = g++-14
CXXFLAGS = -std=c++20

# Always force recompilation
.PHONY: FORCE
FORCE:

# Pattern rule: When running "make filename", compile filename.cpp into a.out
# and run it with filename.in as input.
%: %.cpp FORCE
	$(CXX) $(CXXFLAGS) $< -o a.out
	./a.out < $*.in

# Create a new C++ file with boilerplate and an empty input file
.PHONY: new
new:
	@echo '#include <bits/stdc++.h>\nusing namespace std;\n\nint main() {\n    ios::sync_with_stdio(false);\n    cin.tie(NULL);\n\n  \n    return 0;\n}' > $(basename $(filename)).cpp
	@touch $(basename $(filename)).in
	@echo "Created $(basename $(filename)).cpp and $(basename $(filename)).in"

# Clean: remove the a.out binary
.PHONY: clean
clean:
	rm -f a.out
