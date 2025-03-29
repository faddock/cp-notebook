# Compiler and flags
CXX = g++-14
CXXFLAGS = -std=c++20

# Always force recompilation
.PHONY: FORCE
FORCE:

# Pattern rule: When running "make filename", compile filename.cpp into a.out
# and run it with a.in as input.
%: %.cpp FORCE
	$(CXX) $(CXXFLAGS) $< -o a.out
	./a.out < a.in

# Create a new C++ file with boilerplate and an empty input file
# make new filename=your_file.cpp
.PHONY: new
new:
	@echo '#include <bits/stdc++.h>\nusing namespace std;\n\nint main() {\n    ios::sync_with_stdio(false);\n    cin.tie(NULL);\n    int n; cin >> n;\n  \n    return 0;\n}' > $(basename $(filename)).cpp
	@echo "Created $(basename $(filename)).cpp"

# Clean: remove the a.out binary
# make clean 
.PHONY: clean
clean:
	rm -f a.out

# Custom target to remove one-line comments from a C++ file
# make remove-comments filename=your_file.cpp
.PHONY: remove-comments
remove-comments:
	@echo "Removing one-line comments from $(filename)..."
	@sed -i '' '/^\s*\/\//d' $(filename)  # For macOS
	@echo "Comments removed from $(filename)