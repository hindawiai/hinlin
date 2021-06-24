<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * IOMMU helper functions क्रम the मुक्त area management
 */

#समावेश <linux/biपंचांगap.h>
#समावेश <linux/iommu-helper.h>

अचिन्हित दीर्घ iommu_area_alloc(अचिन्हित दीर्घ *map, अचिन्हित दीर्घ size,
			       अचिन्हित दीर्घ start, अचिन्हित पूर्णांक nr,
			       अचिन्हित दीर्घ shअगरt, अचिन्हित दीर्घ boundary_size,
			       अचिन्हित दीर्घ align_mask)
अणु
	अचिन्हित दीर्घ index;

	/* We करोn't want the last of the limit */
	size -= 1;
again:
	index = biपंचांगap_find_next_zero_area(map, size, start, nr, align_mask);
	अगर (index < size) अणु
		अगर (iommu_is_span_boundary(index, nr, shअगरt, boundary_size)) अणु
			start = ALIGN(shअगरt + index, boundary_size) - shअगरt;
			जाओ again;
		पूर्ण
		biपंचांगap_set(map, index, nr);
		वापस index;
	पूर्ण
	वापस -1;
पूर्ण
