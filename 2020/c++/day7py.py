FNAME = "input_day7.txt"
 
 
def get_rules():
    rules = {}
 
    with open(FNAME, "r") as f:
        for line in f:
            words = line.split()
            description = " ".join(words[:2])
            tail = " ".join(words[4:])
            contents = []
 
            if tail != "no other bags.":
                for bag in tail.split(","):
                    words = bag.strip().split(" ")
                    contents.append((int(words[0]), " ".join(words[1:3])))
 
            rules[description] = contents
 
    return rules
 
 
def check_candidates(bags, rules, target, so_far):
    candidates = set()
 
    for bag in bags:
        if bag in so_far:
            continue  # already found
 
        children = [c[1] for c in rules[bag]]
 
        if children:
            if target in children:
                candidates.add(bag)
            elif len(so_far.intersection(children)) > 0:
                candidates.add(bag)
            else:
                new = check_candidates(children, rules, target, so_far)
                if new:
                    candidates.update(new)
                    candidates.add(bag)
 
    return candidates
 
 
def contents_of(bag, rules):
    children = rules[bag]
    if children == []:
        return []
 
    return [(n, b, contents_of(b, rules)) for n, b in children]
 
 
def fold_node(weight, leaves):
    total = 0
    if leaves != []:
        for n, _, children in leaves:
            total += n * (1 + fold_node(n, children))
    return total
 
 
def part1(rules):
    candidates = set()
 
    for bag in rules:
        candidates.update(check_candidates([bag], rules, "shiny gold", candidates))
 
    print(len(candidates))
 
 
def part2(rules):
    print(fold_node(1, contents_of("shiny gold", rules)))
 
 
RULES = get_rules()
part1(RULES)
part2(RULES)