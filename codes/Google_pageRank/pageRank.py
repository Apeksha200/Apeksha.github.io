import networkx as nx
from networkx.exception import NetworkXError

def pagerank(G, alpha=0.85, personalization=None,
             max_iter=100, tol=1.0e-6, nstart=None, weight='weight',
             dangling=None):
    if len(G) == 0:
        return {}

    # Ensure graph is directed
    if not G.is_directed():
        G = G.to_directed()

    # Create right-stochastic graph (normalize weights)
    W = nx.stochastic_graph(G, weight=weight)
    N = W.number_of_nodes()

    # Initial PageRank vector
    if nstart is None:
        x = dict.fromkeys(W.nodes(), 1.0 / N)
    else:
        s = sum(nstart.values())
        x = {k: v / s for k, v in nstart.items()}

    # Personalization vector
    if personalization is None:
        p = dict.fromkeys(W.nodes(), 1.0 / N)
    else:
        missing = set(W.nodes()) - set(personalization)
        if missing:
            raise NetworkXError(f"Personalization dictionary missing nodes: {missing}")
        s = sum(personalization.values())
        p = {k: v / s for k, v in personalization.items()}

    # Dangling node handling
    if dangling is None:
        dangling_weights = p
    else:
        missing = set(W.nodes()) - set(dangling)
        if missing:
            raise NetworkXError(f"Dangling dictionary missing nodes: {missing}")
        s = sum(dangling.values())
        dangling_weights = {k: v / s for k, v in dangling.items()}

    dangling_nodes = [n for n in W if W.out_degree(n, weight=weight) == 0.0]

    # Power iteration
    for i in range(max_iter):
        xlast = x.copy()
        x = dict.fromkeys(xlast.keys(), 0)
        danglesum = alpha * sum(xlast[n] for n in dangling_nodes)

        for n in W:
            for nbr in W[n]:
                x[nbr] += alpha * xlast[n] * W[n][nbr].get(weight, 1)
            x[n] += danglesum * dangling_weights.get(n, 0) + (1.0 - alpha) * p.get(n, 0)

        err = sum(abs(x[n] - xlast[n]) for n in x)
        if err < N * tol:
            return x

    raise NetworkXError(f"pagerank: power iteration failed to converge in {max_iter} iterations.")


# 💥 STATIC DEMO GRAPH AND FUNCTION CALL
if __name__ == "__main__":
    # 🎯 Create a small directed graph
    G = nx.DiGraph()
    G.add_edges_from([
        ('A', 'B'),
        ('B', 'C'),
        ('C', 'A'),
        ('D', 'C'),
        ('E', 'F'),
        ('F', 'E'),
        ('G', 'F'),
        ('F', 'G')
    ])

    print("✅ Running PageRank...\n")
    pr_scores = pagerank(G)

    print("📊 PageRank Results:")
    for node, score in sorted(pr_scores.items(), key=lambda x: -x[1]):
        print(f"{node}: {score:.4f}")

