<शैली गुरु>
#समावेश <मानक_निवेशt.h>
#समावेश <stdbool.h>

व्योम preserce_ptr_sz_fn(दीर्घ x) अणुपूर्ण

#घोषणा __bpf_aligned __attribute__((aligned(8)))

/*
 * KERNEL
 */

काष्ठा core_reloc_kernel_output अणु
	पूर्णांक valid[10];
	अक्षर comm[माप("test_progs")];
	पूर्णांक comm_len;
पूर्ण;

/*
 * MODULE
 */

काष्ठा core_reloc_module_output अणु
	दीर्घ दीर्घ len;
	दीर्घ दीर्घ off;
	पूर्णांक पढ़ो_ctx_sz;
	bool पढ़ो_ctx_exists;
	bool buf_exists;
	bool len_exists;
	bool off_exists;
	/* we have test_progs[-flavor], so cut flavor part */
	अक्षर comm[माप("test_progs")];
	पूर्णांक comm_len;
पूर्ण;

/*
 * FLAVORS
 */
काष्ठा core_reloc_flavors अणु
	पूर्णांक a;
	पूर्णांक b;
	पूर्णांक c;
पूर्ण;

/* this is not a flavor, as it करोesn't have triple underscore */
काष्ठा core_reloc_flavors__err_wrong_name अणु
	पूर्णांक a;
	पूर्णांक b;
	पूर्णांक c;
पूर्ण;

/*
 * NESTING
 */
/* original set up, used to record relocations in BPF program */
काष्ठा core_reloc_nesting_subकाष्ठा अणु
	पूर्णांक a;
पूर्ण;

जोड़ core_reloc_nesting_subजोड़ अणु
	पूर्णांक b;
पूर्ण;

काष्ठा core_reloc_nesting अणु
	जोड़ अणु
		काष्ठा core_reloc_nesting_subकाष्ठा a;
	पूर्ण a;
	काष्ठा अणु
		जोड़ core_reloc_nesting_subजोड़ b;
	पूर्ण b;
पूर्ण;

/* अंतरभूतd anonymous काष्ठा/जोड़ instead of named काष्ठाs in original */
काष्ठा core_reloc_nesting___anon_embed अणु
	पूर्णांक __just_क्रम_padding;
	जोड़ अणु
		काष्ठा अणु
			पूर्णांक a;
		पूर्ण a;
	पूर्ण a;
	काष्ठा अणु
		जोड़ अणु
			पूर्णांक b;
		पूर्ण b;
	पूर्ण b;
पूर्ण;

/* dअगरferent mix of nested काष्ठाs/जोड़s than in original */
काष्ठा core_reloc_nesting___काष्ठा_जोड़_mixup अणु
	पूर्णांक __a;
	काष्ठा अणु
		पूर्णांक __a;
		जोड़ अणु
			अक्षर __a;
			पूर्णांक a;
		पूर्ण a;
	पूर्ण a;
	पूर्णांक __b;
	जोड़ अणु
		पूर्णांक __b;
		जोड़ अणु
			अक्षर __b;
			पूर्णांक b;
		पूर्ण b;
	पूर्ण b;
पूर्ण;

/* extra anon काष्ठाs/जोड़s, but still valid a.a.a and b.b.b accessors */
काष्ठा core_reloc_nesting___extra_nesting अणु
	पूर्णांक __padding;
	काष्ठा अणु
		काष्ठा अणु
			काष्ठा अणु
				काष्ठा अणु
					जोड़ अणु
						पूर्णांक a;
					पूर्ण a;
				पूर्ण;
			पूर्ण;
		पूर्ण a;
		पूर्णांक __some_more;
		काष्ठा अणु
			जोड़ अणु
				जोड़ अणु
					जोड़ अणु
						काष्ठा अणु
							पूर्णांक b;
						पूर्ण;
					पूर्ण b;
				पूर्ण;
			पूर्ण b;
		पूर्ण;
	पूर्ण;
पूर्ण;

/* three flavors of same काष्ठा with dअगरferent काष्ठाure but same layout क्रम
 * a.a.a and b.b.b, thus successfully resolved and relocatable */
काष्ठा core_reloc_nesting___dup_compat_types अणु
	अक्षर __just_क्रम_padding;
	/* 3 more bytes of padding */
	काष्ठा अणु
		काष्ठा अणु
			पूर्णांक a; /* offset 4 */
		पूर्ण a;
	पूर्ण a;
	दीर्घ दीर्घ __more_padding;
	काष्ठा अणु
		काष्ठा अणु
			पूर्णांक b; /* offset 16 */
		पूर्ण b;
	पूर्ण b;
पूर्ण;

काष्ठा core_reloc_nesting___dup_compat_types__2 अणु
	पूर्णांक __aligned_padding;
	काष्ठा अणु
		पूर्णांक __trickier_noop[0];
		काष्ठा अणु
			अक्षर __some_more_noops[0];
			पूर्णांक a; /* offset 4 */
		पूर्ण a;
	पूर्ण a;
	पूर्णांक __more_padding;
	काष्ठा अणु
		काष्ठा अणु
			काष्ठा अणु
				पूर्णांक __critical_padding;
				पूर्णांक b; /* offset 16 */
			पूर्ण b;
			पूर्णांक __करोes_not_matter;
		पूर्ण;
	पूर्ण b;
	पूर्णांक __more_irrelevant_stuff;
पूर्ण;

काष्ठा core_reloc_nesting___dup_compat_types__3 अणु
	अक्षर __correct_padding[4];
	काष्ठा अणु
		काष्ठा अणु
			पूर्णांक a; /* offset 4 */
		पूर्ण a;
	पूर्ण a;
	/* 8 byte padding due to next काष्ठा's alignment */
	काष्ठा अणु
		काष्ठा अणु
			पूर्णांक b;
		पूर्ण b;
	पूर्ण b __attribute__((aligned(16)));
पूर्ण;

/* b.b.b field is missing */
काष्ठा core_reloc_nesting___err_missing_field अणु
	काष्ठा अणु
		काष्ठा अणु
			पूर्णांक a;
		पूर्ण a;
	पूर्ण a;
	काष्ठा अणु
		काष्ठा अणु
			पूर्णांक x;
		पूर्ण b;
	पूर्ण b;
पूर्ण;

/* b.b.b field is an array of पूर्णांकegers instead of plain पूर्णांक */
काष्ठा core_reloc_nesting___err_array_field अणु
	काष्ठा अणु
		काष्ठा अणु
			पूर्णांक a;
		पूर्ण a;
	पूर्ण a;
	काष्ठा अणु
		काष्ठा अणु
			पूर्णांक b[1];
		पूर्ण b;
	पूर्ण b;
पूर्ण;

/* middle b container is missing */
काष्ठा core_reloc_nesting___err_missing_container अणु
	काष्ठा अणु
		काष्ठा अणु
			पूर्णांक a;
		पूर्ण a;
	पूर्ण a;
	काष्ठा अणु
		पूर्णांक x;
	पूर्ण b;
पूर्ण;

/* middle b container is referenced through poपूर्णांकer instead of being embedded */
काष्ठा core_reloc_nesting___err_nonकाष्ठा_container अणु
	काष्ठा अणु
		काष्ठा अणु
			पूर्णांक a;
		पूर्ण a;
	पूर्ण a;
	काष्ठा अणु
		काष्ठा अणु
			पूर्णांक b;
		पूर्ण *b;
	पूर्ण b;
पूर्ण;

/* middle b container is an array of काष्ठाs instead of plain काष्ठा */
काष्ठा core_reloc_nesting___err_array_container अणु
	काष्ठा अणु
		काष्ठा अणु
			पूर्णांक a;
		पूर्ण a;
	पूर्ण a;
	काष्ठा अणु
		काष्ठा अणु
			पूर्णांक b;
		पूर्ण b[1];
	पूर्ण b;
पूर्ण;

/* two flavors of same काष्ठा with incompatible layout क्रम b.b.b */
काष्ठा core_reloc_nesting___err_dup_incompat_types__1 अणु
	काष्ठा अणु
		काष्ठा अणु
			पूर्णांक a; /* offset 0 */
		पूर्ण a;
	पूर्ण a;
	काष्ठा अणु
		काष्ठा अणु
			पूर्णांक b; /* offset 4 */
		पूर्ण b;
	पूर्ण b;
पूर्ण;

काष्ठा core_reloc_nesting___err_dup_incompat_types__2 अणु
	काष्ठा अणु
		काष्ठा अणु
			पूर्णांक a; /* offset 0 */
		पूर्ण a;
	पूर्ण a;
	पूर्णांक __extra_padding;
	काष्ठा अणु
		काष्ठा अणु
			पूर्णांक b; /* offset 8 (!) */
		पूर्ण b;
	पूर्ण b;
पूर्ण;

/* two flavors of same काष्ठा having one of a.a.a and b.b.b, but not both */
काष्ठा core_reloc_nesting___err_partial_match_dups__a अणु
	काष्ठा अणु
		काष्ठा अणु
			पूर्णांक a;
		पूर्ण a;
	पूर्ण a;
पूर्ण;

काष्ठा core_reloc_nesting___err_partial_match_dups__b अणु
	काष्ठा अणु
		काष्ठा अणु
			पूर्णांक b;
		पूर्ण b;
	पूर्ण b;
पूर्ण;

काष्ठा core_reloc_nesting___err_too_deep अणु
	काष्ठा अणु
		काष्ठा अणु
			पूर्णांक a;
		पूर्ण a;
	पूर्ण a;
	/* 65 levels of nestedness क्रम b.b.b */
	काष्ठा अणु
		काष्ठा अणु
			काष्ठा अणु काष्ठा अणु काष्ठा अणु काष्ठा अणु काष्ठा अणु
			काष्ठा अणु काष्ठा अणु काष्ठा अणु काष्ठा अणु काष्ठा अणु
			काष्ठा अणु काष्ठा अणु काष्ठा अणु काष्ठा अणु काष्ठा अणु
			काष्ठा अणु काष्ठा अणु काष्ठा अणु काष्ठा अणु काष्ठा अणु
			काष्ठा अणु काष्ठा अणु काष्ठा अणु काष्ठा अणु काष्ठा अणु
			काष्ठा अणु काष्ठा अणु काष्ठा अणु काष्ठा अणु काष्ठा अणु
			काष्ठा अणु काष्ठा अणु काष्ठा अणु काष्ठा अणु काष्ठा अणु
			काष्ठा अणु काष्ठा अणु काष्ठा अणु काष्ठा अणु काष्ठा अणु
			काष्ठा अणु काष्ठा अणु काष्ठा अणु काष्ठा अणु काष्ठा अणु
			काष्ठा अणु काष्ठा अणु काष्ठा अणु काष्ठा अणु काष्ठा अणु
			काष्ठा अणु काष्ठा अणु काष्ठा अणु काष्ठा अणु काष्ठा अणु
			काष्ठा अणु काष्ठा अणु काष्ठा अणु काष्ठा अणु काष्ठा अणु
				/* this one is one too much */
				काष्ठा अणु
					पूर्णांक b;
				पूर्ण;
			पूर्ण; पूर्ण; पूर्ण; पूर्ण; पूर्ण;
			पूर्ण; पूर्ण; पूर्ण; पूर्ण; पूर्ण;
			पूर्ण; पूर्ण; पूर्ण; पूर्ण; पूर्ण;
			पूर्ण; पूर्ण; पूर्ण; पूर्ण; पूर्ण;
			पूर्ण; पूर्ण; पूर्ण; पूर्ण; पूर्ण;
			पूर्ण; पूर्ण; पूर्ण; पूर्ण; पूर्ण;
			पूर्ण; पूर्ण; पूर्ण; पूर्ण; पूर्ण;
			पूर्ण; पूर्ण; पूर्ण; पूर्ण; पूर्ण;
			पूर्ण; पूर्ण; पूर्ण; पूर्ण; पूर्ण;
			पूर्ण; पूर्ण; पूर्ण; पूर्ण; पूर्ण;
			पूर्ण; पूर्ण; पूर्ण; पूर्ण; पूर्ण;
			पूर्ण; पूर्ण; पूर्ण; पूर्ण; पूर्ण;
		पूर्ण b;
	पूर्ण b;
पूर्ण;

/*
 * ARRAYS
 */
काष्ठा core_reloc_arrays_output अणु
	पूर्णांक a2;
	अक्षर b123;
	पूर्णांक c1c;
	पूर्णांक d00d;
	पूर्णांक f10c;
पूर्ण;

काष्ठा core_reloc_arrays_subकाष्ठा अणु
	पूर्णांक c;
	पूर्णांक d;
पूर्ण;

काष्ठा core_reloc_arrays अणु
	पूर्णांक a[5];
	अक्षर b[2][3][4];
	काष्ठा core_reloc_arrays_subकाष्ठा c[3];
	काष्ठा core_reloc_arrays_subकाष्ठा d[1][2];
	काष्ठा core_reloc_arrays_subकाष्ठा f[][2];
पूर्ण;

/* bigger array dimensions */
काष्ठा core_reloc_arrays___dअगरf_arr_dim अणु
	पूर्णांक a[7];
	अक्षर b[3][4][5];
	काष्ठा core_reloc_arrays_subकाष्ठा c[4];
	काष्ठा core_reloc_arrays_subकाष्ठा d[2][3];
	काष्ठा core_reloc_arrays_subकाष्ठा f[1][3];
पूर्ण;

/* dअगरferent size of array's value (काष्ठा) */
काष्ठा core_reloc_arrays___dअगरf_arr_val_sz अणु
	पूर्णांक a[5];
	अक्षर b[2][3][4];
	काष्ठा अणु
		पूर्णांक __padding1;
		पूर्णांक c;
		पूर्णांक __padding2;
	पूर्ण c[3];
	काष्ठा अणु
		पूर्णांक __padding1;
		पूर्णांक d;
		पूर्णांक __padding2;
	पूर्ण d[1][2];
	काष्ठा अणु
		पूर्णांक __padding1;
		पूर्णांक c;
		पूर्णांक __padding2;
	पूर्ण f[][2];
पूर्ण;

काष्ठा core_reloc_arrays___equiv_zero_sz_arr अणु
	पूर्णांक a[5];
	अक्षर b[2][3][4];
	काष्ठा core_reloc_arrays_subकाष्ठा c[3];
	काष्ठा core_reloc_arrays_subकाष्ठा d[1][2];
	/* equivalent to flexible array */
	काष्ठा core_reloc_arrays_subकाष्ठा f[][2];
पूर्ण;

काष्ठा core_reloc_arrays___fixed_arr अणु
	पूर्णांक a[5];
	अक्षर b[2][3][4];
	काष्ठा core_reloc_arrays_subकाष्ठा c[3];
	काष्ठा core_reloc_arrays_subकाष्ठा d[1][2];
	/* not a flexible array anymore, but within access bounds */
	काष्ठा core_reloc_arrays_subकाष्ठा f[1][2];
पूर्ण;

काष्ठा core_reloc_arrays___err_too_small अणु
	पूर्णांक a[2]; /* this one is too small */
	अक्षर b[2][3][4];
	काष्ठा core_reloc_arrays_subकाष्ठा c[3];
	काष्ठा core_reloc_arrays_subकाष्ठा d[1][2];
	काष्ठा core_reloc_arrays_subकाष्ठा f[][2];
पूर्ण;

काष्ठा core_reloc_arrays___err_too_shallow अणु
	पूर्णांक a[5];
	अक्षर b[2][3]; /* this one lacks one dimension */
	काष्ठा core_reloc_arrays_subकाष्ठा c[3];
	काष्ठा core_reloc_arrays_subकाष्ठा d[1][2];
	काष्ठा core_reloc_arrays_subकाष्ठा f[][2];
पूर्ण;

काष्ठा core_reloc_arrays___err_non_array अणु
	पूर्णांक a; /* not an array */
	अक्षर b[2][3][4];
	काष्ठा core_reloc_arrays_subकाष्ठा c[3];
	काष्ठा core_reloc_arrays_subकाष्ठा d[1][2];
	काष्ठा core_reloc_arrays_subकाष्ठा f[][2];
पूर्ण;

काष्ठा core_reloc_arrays___err_wrong_val_type अणु
	पूर्णांक a[5];
	अक्षर b[2][3][4];
	पूर्णांक c[3]; /* value is not a काष्ठा */
	काष्ठा core_reloc_arrays_subकाष्ठा d[1][2];
	काष्ठा core_reloc_arrays_subकाष्ठा f[][2];
पूर्ण;

काष्ठा core_reloc_arrays___err_bad_zero_sz_arr अणु
	/* zero-sized array, but not at the end */
	काष्ठा core_reloc_arrays_subकाष्ठा f[0][2];
	पूर्णांक a[5];
	अक्षर b[2][3][4];
	काष्ठा core_reloc_arrays_subकाष्ठा c[3];
	काष्ठा core_reloc_arrays_subकाष्ठा d[1][2];
पूर्ण;

/*
 * PRIMITIVES
 */
क्रमागत core_reloc_primitives_क्रमागत अणु
	A = 0,
	B = 1,
पूर्ण;

काष्ठा core_reloc_primitives अणु
	अक्षर a;
	पूर्णांक b;
	क्रमागत core_reloc_primitives_क्रमागत c;
	व्योम *d __bpf_aligned;
	पूर्णांक (*f)(स्थिर अक्षर *) __bpf_aligned;
पूर्ण;

काष्ठा core_reloc_primitives___dअगरf_क्रमागत_def अणु
	अक्षर a;
	पूर्णांक b;
	व्योम *d __bpf_aligned;
	पूर्णांक (*f)(स्थिर अक्षर *) __bpf_aligned;
	क्रमागत अणु
		X = 100,
		Y = 200,
	पूर्ण c __bpf_aligned; /* अंतरभूत क्रमागत def with dअगरfering set of values */
पूर्ण;

काष्ठा core_reloc_primitives___dअगरf_func_proto अणु
	व्योम (*f)(पूर्णांक) __bpf_aligned; /* incompatible function prototype */
	व्योम *d __bpf_aligned;
	क्रमागत core_reloc_primitives_क्रमागत c __bpf_aligned;
	पूर्णांक b;
	अक्षर a;
पूर्ण;

काष्ठा core_reloc_primitives___dअगरf_ptr_type अणु
	स्थिर अक्षर * स्थिर d __bpf_aligned; /* dअगरferent poपूर्णांकee type + modअगरiers */
	अक्षर a __bpf_aligned;
	पूर्णांक b;
	क्रमागत core_reloc_primitives_क्रमागत c;
	पूर्णांक (*f)(स्थिर अक्षर *) __bpf_aligned;
पूर्ण;

काष्ठा core_reloc_primitives___err_non_क्रमागत अणु
	अक्षर a[1];
	पूर्णांक b;
	पूर्णांक c; /* पूर्णांक instead of क्रमागत */
	व्योम *d __bpf_aligned;
	पूर्णांक (*f)(स्थिर अक्षर *) __bpf_aligned;
पूर्ण;

काष्ठा core_reloc_primitives___err_non_पूर्णांक अणु
	अक्षर a[1];
	पूर्णांक *b __bpf_aligned; /* ptr instead of पूर्णांक */
	क्रमागत core_reloc_primitives_क्रमागत c __bpf_aligned;
	व्योम *d __bpf_aligned;
	पूर्णांक (*f)(स्थिर अक्षर *) __bpf_aligned;
पूर्ण;

काष्ठा core_reloc_primitives___err_non_ptr अणु
	अक्षर a[1];
	पूर्णांक b;
	क्रमागत core_reloc_primitives_क्रमागत c;
	पूर्णांक d; /* पूर्णांक instead of ptr */
	पूर्णांक (*f)(स्थिर अक्षर *) __bpf_aligned;
पूर्ण;

/*
 * MODS
 */
काष्ठा core_reloc_mods_output अणु
	पूर्णांक a, b, c, d, e, f, g, h;
पूर्ण;

प्रकार स्थिर पूर्णांक पूर्णांक_t;
प्रकार स्थिर अक्षर *अक्षर_ptr_t __bpf_aligned;
प्रकार स्थिर पूर्णांक arr_t[7];

काष्ठा core_reloc_mods_subकाष्ठा अणु
	पूर्णांक x;
	पूर्णांक y;
पूर्ण;

प्रकार काष्ठा अणु
	पूर्णांक x;
	पूर्णांक y;
पूर्ण core_reloc_mods_subकाष्ठा_t;

काष्ठा core_reloc_mods अणु
	पूर्णांक a;
	पूर्णांक_t b;
	अक्षर *c __bpf_aligned;
	अक्षर_ptr_t d;
	पूर्णांक e[3] __bpf_aligned;
	arr_t f;
	काष्ठा core_reloc_mods_subकाष्ठा g;
	core_reloc_mods_subकाष्ठा_t h;
पूर्ण;

/* a/b, c/d, e/f, and g/h pairs are swapped */
काष्ठा core_reloc_mods___mod_swap अणु
	पूर्णांक b;
	पूर्णांक_t a;
	अक्षर *d __bpf_aligned;
	अक्षर_ptr_t c;
	पूर्णांक f[3] __bpf_aligned;
	arr_t e;
	काष्ठा अणु
		पूर्णांक y;
		पूर्णांक x;
	पूर्ण h;
	core_reloc_mods_subकाष्ठा_t g;
पूर्ण;

प्रकार पूर्णांक पूर्णांक1_t;
प्रकार पूर्णांक1_t पूर्णांक2_t;
प्रकार पूर्णांक2_t पूर्णांक3_t;

प्रकार पूर्णांक arr1_t[5];
प्रकार arr1_t arr2_t;
प्रकार arr2_t arr3_t;
प्रकार arr3_t arr4_t;

प्रकार स्थिर अक्षर * स्थिर अस्थिर fancy_अक्षर_ptr_t __bpf_aligned;

प्रकार core_reloc_mods_subकाष्ठा_t core_reloc_mods_subकाष्ठा_tt;

/* we need more प्रकारs */
काष्ठा core_reloc_mods___प्रकारs अणु
	core_reloc_mods_subकाष्ठा_tt g;
	core_reloc_mods_subकाष्ठा_tt h;
	arr4_t f;
	arr4_t e;
	fancy_अक्षर_ptr_t d;
	fancy_अक्षर_ptr_t c;
	पूर्णांक3_t b __bpf_aligned;
	पूर्णांक3_t a;
पूर्ण;

/*
 * PTR_AS_ARR
 */
काष्ठा core_reloc_ptr_as_arr अणु
	पूर्णांक a;
पूर्ण;

काष्ठा core_reloc_ptr_as_arr___dअगरf_sz अणु
	पूर्णांक :32; /* padding */
	अक्षर __some_more_padding;
	पूर्णांक a;
पूर्ण;

/*
 * INTS
 */
काष्ठा core_reloc_पूर्णांकs अणु
	uपूर्णांक8_t		u8_field;
	पूर्णांक8_t		s8_field;
	uपूर्णांक16_t	u16_field;
	पूर्णांक16_t		s16_field;
	uपूर्णांक32_t	u32_field;
	पूर्णांक32_t		s32_field;
	uपूर्णांक64_t	u64_field;
	पूर्णांक64_t		s64_field;
पूर्ण;

/* चिन्हित/अचिन्हित types swap */
काष्ठा core_reloc_पूर्णांकs___reverse_sign अणु
	पूर्णांक8_t		u8_field;
	uपूर्णांक8_t		s8_field;
	पूर्णांक16_t		u16_field;
	uपूर्णांक16_t	s16_field;
	पूर्णांक32_t		u32_field;
	uपूर्णांक32_t	s32_field;
	पूर्णांक64_t		u64_field;
	uपूर्णांक64_t	s64_field;
पूर्ण;

काष्ठा core_reloc_पूर्णांकs___bool अणु
	bool		u8_field; /* bool instead of uपूर्णांक8 */
	पूर्णांक8_t		s8_field;
	uपूर्णांक16_t	u16_field;
	पूर्णांक16_t		s16_field;
	uपूर्णांक32_t	u32_field;
	पूर्णांक32_t		s32_field;
	uपूर्णांक64_t	u64_field;
	पूर्णांक64_t		s64_field;
पूर्ण;

/*
 * MISC
 */
काष्ठा core_reloc_misc_output अणु
	पूर्णांक a, b, c;
पूर्ण;

काष्ठा core_reloc_misc___a अणु
	पूर्णांक a1;
	पूर्णांक a2;
पूर्ण;

काष्ठा core_reloc_misc___b अणु
	पूर्णांक b1;
	पूर्णांक b2;
पूर्ण;

/* this one extends core_reloc_misc_extensible काष्ठा from BPF prog */
काष्ठा core_reloc_misc_extensible अणु
	पूर्णांक a;
	पूर्णांक b;
	पूर्णांक c;
	पूर्णांक d;
पूर्ण;

/*
 * FIELD EXISTENCE
 */
काष्ठा core_reloc_existence_output अणु
	पूर्णांक a_exists;
	पूर्णांक a_value;
	पूर्णांक b_exists;
	पूर्णांक b_value;
	पूर्णांक c_exists;
	पूर्णांक c_value;
	पूर्णांक arr_exists;
	पूर्णांक arr_value;
	पूर्णांक s_exists;
	पूर्णांक s_value;
पूर्ण;

काष्ठा core_reloc_existence अणु
	पूर्णांक a;
	काष्ठा अणु
		पूर्णांक b;
	पूर्ण;
	पूर्णांक c;
	पूर्णांक arr[1];
	काष्ठा अणु
		पूर्णांक x;
	पूर्ण s;
पूर्ण;

काष्ठा core_reloc_existence___minimal अणु
	पूर्णांक a;
पूर्ण;

काष्ठा core_reloc_existence___wrong_field_defs अणु
	व्योम *a;
	पूर्णांक b[1];
	काष्ठाअणु पूर्णांक x; पूर्ण c;
	पूर्णांक arr;
	पूर्णांक s;
पूर्ण;

/*
 * BITFIELDS
 */
/* bitfield पढ़ो results, all as plain पूर्णांकegers */
काष्ठा core_reloc_bitfields_output अणु
	पूर्णांक64_t		ub1;
	पूर्णांक64_t		ub2;
	पूर्णांक64_t		ub7;
	पूर्णांक64_t		sb4;
	पूर्णांक64_t		sb20;
	पूर्णांक64_t		u32;
	पूर्णांक64_t		s32;
पूर्ण;

काष्ठा core_reloc_bitfields अणु
	/* अचिन्हित bitfields */
	uपूर्णांक8_t		ub1: 1;
	uपूर्णांक8_t		ub2: 2;
	uपूर्णांक32_t	ub7: 7;
	/* चिन्हित bitfields */
	पूर्णांक8_t		sb4: 4;
	पूर्णांक32_t		sb20: 20;
	/* non-bitfields */
	uपूर्णांक32_t	u32;
	पूर्णांक32_t		s32;
पूर्ण;

/* dअगरferent bit sizes (both up and करोwn) */
काष्ठा core_reloc_bitfields___bit_sz_change अणु
	/* अचिन्हित bitfields */
	uपूर्णांक16_t	ub1: 3;		/*  1 ->  3 */
	uपूर्णांक32_t	ub2: 20;	/*  2 -> 20 */
	uपूर्णांक8_t		ub7: 1;		/*  7 ->  1 */
	/* चिन्हित bitfields */
	पूर्णांक8_t		sb4: 1;		/*  4 ->  1 */
	पूर्णांक32_t		sb20: 30;	/* 20 -> 30 */
	/* non-bitfields */
	uपूर्णांक16_t	u32;			/* 32 -> 16 */
	पूर्णांक64_t		s32 __bpf_aligned;	/* 32 -> 64 */
पूर्ण;

/* turn bitfield पूर्णांकo non-bitfield and vice versa */
काष्ठा core_reloc_bitfields___bitfield_vs_पूर्णांक अणु
	uपूर्णांक64_t	ub1;		/*  3 -> 64 non-bitfield */
	uपूर्णांक8_t		ub2;		/* 20 ->  8 non-bitfield */
	पूर्णांक64_t		ub7 __bpf_aligned;	/*  7 -> 64 non-bitfield चिन्हित */
	पूर्णांक64_t		sb4 __bpf_aligned;	/*  4 -> 64 non-bitfield चिन्हित */
	uपूर्णांक64_t	sb20 __bpf_aligned;	/* 20 -> 16 non-bitfield अचिन्हित */
	पूर्णांक32_t		u32: 20;		/* 32 non-bitfield -> 20 bitfield */
	uपूर्णांक64_t	s32: 60 __bpf_aligned;	/* 32 non-bitfield -> 60 bitfield */
पूर्ण;

काष्ठा core_reloc_bitfields___just_big_enough अणु
	uपूर्णांक64_t	ub1: 4;
	uपूर्णांक64_t	ub2: 60; /* packed tightly */
	uपूर्णांक32_t	ub7;
	uपूर्णांक32_t	sb4;
	uपूर्णांक32_t	sb20;
	uपूर्णांक32_t	u32;
	uपूर्णांक32_t	s32;
पूर्ण __attribute__((packed)) ;

काष्ठा core_reloc_bitfields___err_too_big_bitfield अणु
	uपूर्णांक64_t	ub1: 4;
	uपूर्णांक64_t	ub2: 61; /* packed tightly */
	uपूर्णांक32_t	ub7;
	uपूर्णांक32_t	sb4;
	uपूर्णांक32_t	sb20;
	uपूर्णांक32_t	u32;
	uपूर्णांक32_t	s32;
पूर्ण __attribute__((packed)) ;

/*
 * SIZE
 */
काष्ठा core_reloc_size_output अणु
	पूर्णांक पूर्णांक_sz;
	पूर्णांक काष्ठा_sz;
	पूर्णांक जोड़_sz;
	पूर्णांक arr_sz;
	पूर्णांक arr_elem_sz;
	पूर्णांक ptr_sz;
	पूर्णांक क्रमागत_sz;
	पूर्णांक भग्न_sz;
पूर्ण;

काष्ठा core_reloc_size अणु
	पूर्णांक पूर्णांक_field;
	काष्ठा अणु पूर्णांक x; पूर्ण काष्ठा_field;
	जोड़ अणु पूर्णांक x; पूर्ण जोड़_field;
	पूर्णांक arr_field[4];
	व्योम *ptr_field;
	क्रमागत अणु VALUE = 123 पूर्ण क्रमागत_field;
	भग्न भग्न_field;
पूर्ण;

काष्ठा core_reloc_size___dअगरf_sz अणु
	uपूर्णांक64_t पूर्णांक_field;
	काष्ठा अणु पूर्णांक x; पूर्णांक y; पूर्णांक z; पूर्ण काष्ठा_field;
	जोड़ अणु पूर्णांक x; अक्षर bla[123]; पूर्ण जोड़_field;
	अक्षर arr_field[10];
	व्योम *ptr_field;
	क्रमागत अणु OTHER_VALUE = 0xFFFFFFFFFFFFFFFF पूर्ण क्रमागत_field;
	द्विगुन भग्न_field;
पूर्ण;

/* Error हाल of two candidates with the fields (पूर्णांक_field) at the same
 * offset, but with dअगरfering final relocation values: size 4 vs size 1
 */
काष्ठा core_reloc_size___err_ambiguous1 अणु
	/* पूर्णांक at offset 0 */
	पूर्णांक पूर्णांक_field;

	काष्ठा अणु पूर्णांक x; पूर्ण काष्ठा_field;
	जोड़ अणु पूर्णांक x; पूर्ण जोड़_field;
	पूर्णांक arr_field[4];
	व्योम *ptr_field;
	क्रमागत अणु VALUE___1 = 123 पूर्ण क्रमागत_field;
	भग्न भग्न_field;
पूर्ण;

काष्ठा core_reloc_size___err_ambiguous2 अणु
	/* अक्षर at offset 0 */
	अक्षर पूर्णांक_field;

	काष्ठा अणु पूर्णांक x; पूर्ण काष्ठा_field;
	जोड़ अणु पूर्णांक x; पूर्ण जोड़_field;
	पूर्णांक arr_field[4];
	व्योम *ptr_field;
	क्रमागत अणु VALUE___2 = 123 पूर्ण क्रमागत_field;
	भग्न भग्न_field;
पूर्ण;

/*
 * TYPE EXISTENCE & SIZE
 */
काष्ठा core_reloc_type_based_output अणु
	bool काष्ठा_exists;
	bool जोड़_exists;
	bool क्रमागत_exists;
	bool प्रकार_named_काष्ठा_exists;
	bool प्रकार_anon_काष्ठा_exists;
	bool प्रकार_काष्ठा_ptr_exists;
	bool प्रकार_पूर्णांक_exists;
	bool प्रकार_क्रमागत_exists;
	bool प्रकार_व्योम_ptr_exists;
	bool प्रकार_func_proto_exists;
	bool प्रकार_arr_exists;

	पूर्णांक काष्ठा_sz;
	पूर्णांक जोड़_sz;
	पूर्णांक क्रमागत_sz;
	पूर्णांक प्रकार_named_काष्ठा_sz;
	पूर्णांक प्रकार_anon_काष्ठा_sz;
	पूर्णांक प्रकार_काष्ठा_ptr_sz;
	पूर्णांक प्रकार_पूर्णांक_sz;
	पूर्णांक प्रकार_क्रमागत_sz;
	पूर्णांक प्रकार_व्योम_ptr_sz;
	पूर्णांक प्रकार_func_proto_sz;
	पूर्णांक प्रकार_arr_sz;
पूर्ण;

काष्ठा a_काष्ठा अणु
	पूर्णांक x;
पूर्ण;

जोड़ a_जोड़ अणु
	पूर्णांक y;
	पूर्णांक z;
पूर्ण;

प्रकार काष्ठा a_काष्ठा named_काष्ठा_प्रकार;

प्रकार काष्ठा अणु पूर्णांक x, y, z; पूर्ण anon_काष्ठा_प्रकार;

प्रकार काष्ठा अणु
	पूर्णांक a, b, c;
पूर्ण *काष्ठा_ptr_प्रकार;

क्रमागत an_क्रमागत अणु
	AN_ENUM_VAL1 = 1,
	AN_ENUM_VAL2 = 2,
	AN_ENUM_VAL3 = 3,
पूर्ण;

प्रकार पूर्णांक पूर्णांक_प्रकार;

प्रकार क्रमागत अणु TYPEDEF_ENUM_VAL1, TYPEDEF_ENUM_VAL2 पूर्ण क्रमागत_प्रकार;

प्रकार व्योम *व्योम_ptr_प्रकार;

प्रकार पूर्णांक (*func_proto_प्रकार)(दीर्घ);

प्रकार अक्षर arr_प्रकार[20];

काष्ठा core_reloc_type_based अणु
	काष्ठा a_काष्ठा f1;
	जोड़ a_जोड़ f2;
	क्रमागत an_क्रमागत f3;
	named_काष्ठा_प्रकार f4;
	anon_काष्ठा_प्रकार f5;
	काष्ठा_ptr_प्रकार f6;
	पूर्णांक_प्रकार f7;
	क्रमागत_प्रकार f8;
	व्योम_ptr_प्रकार f9;
	func_proto_प्रकार f10;
	arr_प्रकार f11;
पूर्ण;

/* no types in target */
काष्ठा core_reloc_type_based___all_missing अणु
पूर्ण;

/* dअगरferent type sizes, extra modअगरiers, anon vs named क्रमागतs, etc */
काष्ठा a_काष्ठा___dअगरf_sz अणु
	दीर्घ x;
	पूर्णांक y;
	अक्षर z;
पूर्ण;

जोड़ a_जोड़___dअगरf_sz अणु
	अक्षर yy;
	अक्षर zz;
पूर्ण;

प्रकार काष्ठा a_काष्ठा___dअगरf_sz named_काष्ठा_प्रकार___dअगरf_sz;

प्रकार काष्ठा अणु दीर्घ xx, yy, zzz; पूर्ण anon_काष्ठा_प्रकार___dअगरf_sz;

प्रकार काष्ठा अणु
	अक्षर aa[1], bb[2], cc[3];
पूर्ण *काष्ठा_ptr_प्रकार___dअगरf_sz;

क्रमागत an_क्रमागत___dअगरf_sz अणु
	AN_ENUM_VAL1___dअगरf_sz = 0x123412341234,
	AN_ENUM_VAL2___dअगरf_sz = 2,
पूर्ण;

प्रकार अचिन्हित दीर्घ पूर्णांक_प्रकार___dअगरf_sz;

प्रकार क्रमागत an_क्रमागत___dअगरf_sz क्रमागत_प्रकार___dअगरf_sz;

प्रकार स्थिर व्योम * स्थिर व्योम_ptr_प्रकार___dअगरf_sz;

प्रकार पूर्णांक_प्रकार___dअगरf_sz (*func_proto_प्रकार___dअगरf_sz)(अक्षर);

प्रकार पूर्णांक arr_प्रकार___dअगरf_sz[2];

काष्ठा core_reloc_type_based___dअगरf_sz अणु
	काष्ठा a_काष्ठा___dअगरf_sz f1;
	जोड़ a_जोड़___dअगरf_sz f2;
	क्रमागत an_क्रमागत___dअगरf_sz f3;
	named_काष्ठा_प्रकार___dअगरf_sz f4;
	anon_काष्ठा_प्रकार___dअगरf_sz f5;
	काष्ठा_ptr_प्रकार___dअगरf_sz f6;
	पूर्णांक_प्रकार___dअगरf_sz f7;
	क्रमागत_प्रकार___dअगरf_sz f8;
	व्योम_ptr_प्रकार___dअगरf_sz f9;
	func_proto_प्रकार___dअगरf_sz f10;
	arr_प्रकार___dअगरf_sz f11;
पूर्ण;

/* incompatibilities between target and local types */
जोड़ a_काष्ठा___incompat अणु /* जोड़ instead of काष्ठा */
	पूर्णांक x;
पूर्ण;

काष्ठा a_जोड़___incompat अणु /* काष्ठा instead of जोड़ */
	पूर्णांक y;
	पूर्णांक z;
पूर्ण;

/* प्रकार to जोड़, not to काष्ठा */
प्रकार जोड़ a_काष्ठा___incompat named_काष्ठा_प्रकार___incompat;

/* प्रकार to व्योम poपूर्णांकer, instead of काष्ठा */
प्रकार व्योम *anon_काष्ठा_प्रकार___incompat;

/* extra poपूर्णांकer indirection */
प्रकार काष्ठा अणु
	पूर्णांक a, b, c;
पूर्ण **काष्ठा_ptr_प्रकार___incompat;

/* प्रकार of a काष्ठा with पूर्णांक, instead of पूर्णांक */
प्रकार काष्ठा अणु पूर्णांक x; पूर्ण पूर्णांक_प्रकार___incompat;

/* प्रकार to func_proto, instead of क्रमागत */
प्रकार पूर्णांक (*क्रमागत_प्रकार___incompat)(व्योम);

/* poपूर्णांकer to अक्षर instead of व्योम */
प्रकार अक्षर *व्योम_ptr_प्रकार___incompat;

/* व्योम वापस type instead of पूर्णांक */
प्रकार व्योम (*func_proto_प्रकार___incompat)(दीर्घ);

/* multi-dimensional array instead of a single-dimensional */
प्रकार पूर्णांक arr_प्रकार___incompat[20][2];

काष्ठा core_reloc_type_based___incompat अणु
	जोड़ a_काष्ठा___incompat f1;
	काष्ठा a_जोड़___incompat f2;
	/* the only valid one is क्रमागत, to check that something still succeeds */
	क्रमागत an_क्रमागत f3;
	named_काष्ठा_प्रकार___incompat f4;
	anon_काष्ठा_प्रकार___incompat f5;
	काष्ठा_ptr_प्रकार___incompat f6;
	पूर्णांक_प्रकार___incompat f7;
	क्रमागत_प्रकार___incompat f8;
	व्योम_ptr_प्रकार___incompat f9;
	func_proto_प्रकार___incompat f10;
	arr_प्रकार___incompat f11;
पूर्ण;

/* func_proto with incompatible signature */
प्रकार व्योम (*func_proto_प्रकार___fn_wrong_ret1)(दीर्घ);
प्रकार पूर्णांक * (*func_proto_प्रकार___fn_wrong_ret2)(दीर्घ);
प्रकार काष्ठा अणु पूर्णांक x; पूर्ण पूर्णांक_काष्ठा_प्रकार;
प्रकार पूर्णांक_काष्ठा_प्रकार (*func_proto_प्रकार___fn_wrong_ret3)(दीर्घ);
प्रकार पूर्णांक (*func_proto_प्रकार___fn_wrong_arg)(व्योम *);
प्रकार पूर्णांक (*func_proto_प्रकार___fn_wrong_arg_cnt1)(दीर्घ, दीर्घ);
प्रकार पूर्णांक (*func_proto_प्रकार___fn_wrong_arg_cnt2)(व्योम);

काष्ठा core_reloc_type_based___fn_wrong_args अणु
	/* one valid type to make sure relos still work */
	काष्ठा a_काष्ठा f1;
	func_proto_प्रकार___fn_wrong_ret1 f2;
	func_proto_प्रकार___fn_wrong_ret2 f3;
	func_proto_प्रकार___fn_wrong_ret3 f4;
	func_proto_प्रकार___fn_wrong_arg f5;
	func_proto_प्रकार___fn_wrong_arg_cnt1 f6;
	func_proto_प्रकार___fn_wrong_arg_cnt2 f7;
पूर्ण;

/*
 * TYPE ID MAPPING (LOCAL AND TARGET)
 */
काष्ठा core_reloc_type_id_output अणु
	पूर्णांक local_anon_काष्ठा;
	पूर्णांक local_anon_जोड़;
	पूर्णांक local_anon_क्रमागत;
	पूर्णांक local_anon_func_proto_ptr;
	पूर्णांक local_anon_व्योम_ptr;
	पूर्णांक local_anon_arr;

	पूर्णांक local_काष्ठा;
	पूर्णांक local_जोड़;
	पूर्णांक local_क्रमागत;
	पूर्णांक local_पूर्णांक;
	पूर्णांक local_काष्ठा_प्रकार;
	पूर्णांक local_func_proto_प्रकार;
	पूर्णांक local_arr_प्रकार;

	पूर्णांक targ_काष्ठा;
	पूर्णांक targ_जोड़;
	पूर्णांक targ_क्रमागत;
	पूर्णांक targ_पूर्णांक;
	पूर्णांक targ_काष्ठा_प्रकार;
	पूर्णांक targ_func_proto_प्रकार;
	पूर्णांक targ_arr_प्रकार;
पूर्ण;

काष्ठा core_reloc_type_id अणु
	काष्ठा a_काष्ठा f1;
	जोड़ a_जोड़ f2;
	क्रमागत an_क्रमागत f3;
	named_काष्ठा_प्रकार f4;
	func_proto_प्रकार f5;
	arr_प्रकार f6;
पूर्ण;

काष्ठा core_reloc_type_id___missing_tarमाला_लो अणु
	/* nothing */
पूर्ण;

/*
 * ENUMERATOR VALUE EXISTENCE AND VALUE RELOCATION
 */
काष्ठा core_reloc_क्रमागतval_output अणु
	bool named_val1_exists;
	bool named_val2_exists;
	bool named_val3_exists;
	bool anon_val1_exists;
	bool anon_val2_exists;
	bool anon_val3_exists;

	पूर्णांक named_val1;
	पूर्णांक named_val2;
	पूर्णांक anon_val1;
	पूर्णांक anon_val2;
पूर्ण;

क्रमागत named_क्रमागत अणु
	NAMED_ENUM_VAL1 = 1,
	NAMED_ENUM_VAL2 = 2,
	NAMED_ENUM_VAL3 = 3,
पूर्ण;

प्रकार क्रमागत अणु
	ANON_ENUM_VAL1 = 0x10,
	ANON_ENUM_VAL2 = 0x20,
	ANON_ENUM_VAL3 = 0x30,
पूर्ण anon_क्रमागत;

काष्ठा core_reloc_क्रमागतval अणु
	क्रमागत named_क्रमागत f1;
	anon_क्रमागत f2;
पूर्ण;

/* dअगरfering क्रमागतerator values */
क्रमागत named_क्रमागत___dअगरf अणु
	NAMED_ENUM_VAL1___dअगरf = 101,
	NAMED_ENUM_VAL2___dअगरf = 202,
	NAMED_ENUM_VAL3___dअगरf = 303,
पूर्ण;

प्रकार क्रमागत अणु
	ANON_ENUM_VAL1___dअगरf = 0x11,
	ANON_ENUM_VAL2___dअगरf = 0x22,
	ANON_ENUM_VAL3___dअगरf = 0x33,
पूर्ण anon_क्रमागत___dअगरf;

काष्ठा core_reloc_क्रमागतval___dअगरf अणु
	क्रमागत named_क्रमागत___dअगरf f1;
	anon_क्रमागत___dअगरf f2;
पूर्ण;

/* missing (optional) third क्रमागत value */
क्रमागत named_क्रमागत___val3_missing अणु
	NAMED_ENUM_VAL1___val3_missing = 111,
	NAMED_ENUM_VAL2___val3_missing = 222,
पूर्ण;

प्रकार क्रमागत अणु
	ANON_ENUM_VAL1___val3_missing = 0x111,
	ANON_ENUM_VAL2___val3_missing = 0x222,
पूर्ण anon_क्रमागत___val3_missing;

काष्ठा core_reloc_क्रमागतval___val3_missing अणु
	क्रमागत named_क्रमागत___val3_missing f1;
	anon_क्रमागत___val3_missing f2;
पूर्ण;

/* missing (mandatory) second क्रमागत value, should fail */
क्रमागत named_क्रमागत___err_missing अणु
	NAMED_ENUM_VAL1___err_missing = 1,
	NAMED_ENUM_VAL3___err_missing = 3,
पूर्ण;

प्रकार क्रमागत अणु
	ANON_ENUM_VAL1___err_missing = 0x111,
	ANON_ENUM_VAL3___err_missing = 0x222,
पूर्ण anon_क्रमागत___err_missing;

काष्ठा core_reloc_क्रमागतval___err_missing अणु
	क्रमागत named_क्रमागत___err_missing f1;
	anon_क्रमागत___err_missing f2;
पूर्ण;
