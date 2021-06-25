<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#अगर_अघोषित _MEDIA_FRAME_VECTOR_H
#घोषणा _MEDIA_FRAME_VECTOR_H

/* Container क्रम pinned pfns / pages in frame_vector.c */
काष्ठा frame_vector अणु
	अचिन्हित पूर्णांक nr_allocated;	/* Number of frames we have space क्रम */
	अचिन्हित पूर्णांक nr_frames;	/* Number of frames stored in ptrs array */
	bool got_ref;		/* Did we pin pages by getting page ref? */
	bool is_pfns;		/* Does array contain pages or pfns? */
	व्योम *ptrs[];		/* Array of pinned pfns / pages. Use
				 * pfns_vector_pages() or pfns_vector_pfns()
				 * क्रम access */
पूर्ण;

काष्ठा frame_vector *frame_vector_create(अचिन्हित पूर्णांक nr_frames);
व्योम frame_vector_destroy(काष्ठा frame_vector *vec);
पूर्णांक get_vaddr_frames(अचिन्हित दीर्घ start, अचिन्हित पूर्णांक nr_pfns,
		     काष्ठा frame_vector *vec);
व्योम put_vaddr_frames(काष्ठा frame_vector *vec);
पूर्णांक frame_vector_to_pages(काष्ठा frame_vector *vec);
व्योम frame_vector_to_pfns(काष्ठा frame_vector *vec);

अटल अंतरभूत अचिन्हित पूर्णांक frame_vector_count(काष्ठा frame_vector *vec)
अणु
	वापस vec->nr_frames;
पूर्ण

अटल अंतरभूत काष्ठा page **frame_vector_pages(काष्ठा frame_vector *vec)
अणु
	अगर (vec->is_pfns) अणु
		पूर्णांक err = frame_vector_to_pages(vec);

		अगर (err)
			वापस ERR_PTR(err);
	पूर्ण
	वापस (काष्ठा page **)(vec->ptrs);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ *frame_vector_pfns(काष्ठा frame_vector *vec)
अणु
	अगर (!vec->is_pfns)
		frame_vector_to_pfns(vec);
	वापस (अचिन्हित दीर्घ *)(vec->ptrs);
पूर्ण

#पूर्ण_अगर /* _MEDIA_FRAME_VECTOR_H */
