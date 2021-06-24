<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/dma-mapping.h>
#समावेश <यंत्र/iommu_table.h>
#समावेश <linux/माला.स>
#समावेश <linux/kallsyms.h>

अटल काष्ठा iommu_table_entry * __init
find_dependents_of(काष्ठा iommu_table_entry *start,
		   काष्ठा iommu_table_entry *finish,
		   काष्ठा iommu_table_entry *q)
अणु
	काष्ठा iommu_table_entry *p;

	अगर (!q)
		वापस शून्य;

	क्रम (p = start; p < finish; p++)
		अगर (p->detect == q->depend)
			वापस p;

	वापस शून्य;
पूर्ण


व्योम __init sort_iommu_table(काष्ठा iommu_table_entry *start,
			     काष्ठा iommu_table_entry *finish) अणु

	काष्ठा iommu_table_entry *p, *q, पंचांगp;

	क्रम (p = start; p < finish; p++) अणु
again:
		q = find_dependents_of(start, finish, p);
		/* We are bit sneaky here. We use the memory address to figure
		 * out अगर the node we depend on is past our poपूर्णांक, अगर so, swap.
		 */
		अगर (q > p) अणु
			पंचांगp = *p;
			स_हटाओ(p, q, माप(*p));
			*q = पंचांगp;
			जाओ again;
		पूर्ण
	पूर्ण

पूर्ण

#अगर_घोषित DEBUG
व्योम __init check_iommu_entries(काष्ठा iommu_table_entry *start,
				काष्ठा iommu_table_entry *finish)
अणु
	काष्ठा iommu_table_entry *p, *q, *x;

	/* Simple cyclic dependency checker. */
	क्रम (p = start; p < finish; p++) अणु
		q = find_dependents_of(start, finish, p);
		x = find_dependents_of(start, finish, q);
		अगर (p == x) अणु
			prपूर्णांकk(KERN_ERR "CYCLIC DEPENDENCY FOUND! %pS depends on %pS and vice-versa. BREAKING IT.\n",
			       p->detect, q->detect);
			/* Heavy handed way..*/
			x->depend = शून्य;
		पूर्ण
	पूर्ण

	क्रम (p = start; p < finish; p++) अणु
		q = find_dependents_of(p, finish, p);
		अगर (q && q > p) अणु
			prपूर्णांकk(KERN_ERR "EXECUTION ORDER INVALID! %pS should be called before %pS!\n",
			       p->detect, q->detect);
		पूर्ण
	पूर्ण
पूर्ण
#अन्यथा
व्योम __init check_iommu_entries(काष्ठा iommu_table_entry *start,
				       काष्ठा iommu_table_entry *finish)
अणु
पूर्ण
#पूर्ण_अगर
