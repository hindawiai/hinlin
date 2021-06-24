<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * These काष्ठाs are used by the प्रणाली-use-sharing protocol, in which the
 * Rock Ridge extensions are embedded.  It is quite possible that other
 * extensions are present on the disk, and this is fine as दीर्घ as they
 * all use SUSP
 */

काष्ठा SU_SP_s अणु
	__u8 magic[2];
	__u8 skip;
पूर्ण __attribute__ ((packed));

काष्ठा SU_CE_s अणु
	__u8 extent[8];
	__u8 offset[8];
	__u8 size[8];
पूर्ण;

काष्ठा SU_ER_s अणु
	__u8 len_id;
	__u8 len_des;
	__u8 len_src;
	__u8 ext_ver;
	__u8 data[];
पूर्ण __attribute__ ((packed));

काष्ठा RR_RR_s अणु
	__u8 flags[1];
पूर्ण __attribute__ ((packed));

काष्ठा RR_PX_s अणु
	__u8 mode[8];
	__u8 n_links[8];
	__u8 uid[8];
	__u8 gid[8];
पूर्ण;

काष्ठा RR_PN_s अणु
	__u8 dev_high[8];
	__u8 dev_low[8];
पूर्ण;

काष्ठा SL_component अणु
	__u8 flags;
	__u8 len;
	__u8 text[];
पूर्ण __attribute__ ((packed));

काष्ठा RR_SL_s अणु
	__u8 flags;
	काष्ठा SL_component link;
पूर्ण __attribute__ ((packed));

काष्ठा RR_NM_s अणु
	__u8 flags;
	अक्षर name[];
पूर्ण __attribute__ ((packed));

काष्ठा RR_CL_s अणु
	__u8 location[8];
पूर्ण;

काष्ठा RR_PL_s अणु
	__u8 location[8];
पूर्ण;

काष्ठा stamp अणु
	__u8 समय[7];		/* actually 6 अचिन्हित, 1 चिन्हित */
पूर्ण __attribute__ ((packed));

काष्ठा RR_TF_s अणु
	__u8 flags;
	काष्ठा stamp बार[];	/* Variable number of these beasts */
पूर्ण __attribute__ ((packed));

/* Linux-specअगरic extension क्रम transparent decompression */
काष्ठा RR_ZF_s अणु
	__u8 algorithm[2];
	__u8 parms[2];
	__u8 real_size[8];
पूर्ण;

/*
 * These are the bits and their meanings क्रम flags in the TF काष्ठाure.
 */
#घोषणा TF_CREATE 1
#घोषणा TF_MODIFY 2
#घोषणा TF_ACCESS 4
#घोषणा TF_ATTRIBUTES 8
#घोषणा TF_BACKUP 16
#घोषणा TF_EXPIRATION 32
#घोषणा TF_EFFECTIVE 64
#घोषणा TF_LONG_FORM 128

काष्ठा rock_ridge अणु
	__u8 signature[2];
	__u8 len;
	__u8 version;
	जोड़ अणु
		काष्ठा SU_SP_s SP;
		काष्ठा SU_CE_s CE;
		काष्ठा SU_ER_s ER;
		काष्ठा RR_RR_s RR;
		काष्ठा RR_PX_s PX;
		काष्ठा RR_PN_s PN;
		काष्ठा RR_SL_s SL;
		काष्ठा RR_NM_s NM;
		काष्ठा RR_CL_s CL;
		काष्ठा RR_PL_s PL;
		काष्ठा RR_TF_s TF;
		काष्ठा RR_ZF_s ZF;
	पूर्ण u;
पूर्ण;

#घोषणा RR_PX 1			/* POSIX attributes */
#घोषणा RR_PN 2			/* POSIX devices */
#घोषणा RR_SL 4			/* Symbolic link */
#घोषणा RR_NM 8			/* Alternate Name */
#घोषणा RR_CL 16		/* Child link */
#घोषणा RR_PL 32		/* Parent link */
#घोषणा RR_RE 64		/* Relocation directory */
#घोषणा RR_TF 128		/* Timestamps */
