<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SELFTESTS_POWERPC_INSTRUCTIONS_H
#घोषणा _SELFTESTS_POWERPC_INSTRUCTIONS_H

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>

/* This defines the "copy" inकाष्ठाion from Power ISA 3.0 Book II, section 4.4. */
#घोषणा __COPY(RA, RB, L) \
	(0x7c00060c | (RA) << (31-15) | (RB) << (31-20) | (L) << (31-10))
#घोषणा COPY(RA, RB, L) \
	.दीर्घ __COPY((RA), (RB), (L))

अटल अंतरभूत व्योम copy(व्योम *i)
अणु
	यंत्र अस्थिर(str(COPY(0, %0, 0))";"
			:
			: "b" (i)
			: "memory"
		    );
पूर्ण

अटल अंतरभूत व्योम copy_first(व्योम *i)
अणु
	यंत्र अस्थिर(str(COPY(0, %0, 1))";"
			:
			: "b" (i)
			: "memory"
		    );
पूर्ण

/* This defines the "paste" inकाष्ठाion from Power ISA 3.0 Book II, section 4.4. */
#घोषणा __PASTE(RA, RB, L, RC) \
	(0x7c00070c | (RA) << (31-15) | (RB) << (31-20) | (L) << (31-10) | (RC) << (31-31))
#घोषणा PASTE(RA, RB, L, RC) \
	.दीर्घ __PASTE((RA), (RB), (L), (RC))

अटल अंतरभूत पूर्णांक paste(व्योम *i)
अणु
	पूर्णांक cr;

	यंत्र अस्थिर(str(PASTE(0, %1, 0, 0))";"
			"mfcr %0;"
			: "=r" (cr)
			: "b" (i)
			: "memory"
		    );
	वापस cr;
पूर्ण

अटल अंतरभूत पूर्णांक paste_last(व्योम *i)
अणु
	पूर्णांक cr;

	यंत्र अस्थिर(str(PASTE(0, %1, 1, 1))";"
			"mfcr %0;"
			: "=r" (cr)
			: "b" (i)
			: "memory"
		    );
	वापस cr;
पूर्ण

#घोषणा PPC_INST_COPY                  __COPY(0, 0, 0)
#घोषणा PPC_INST_COPY_FIRST            __COPY(0, 0, 1)
#घोषणा PPC_INST_PASTE                 __PASTE(0, 0, 0, 0)
#घोषणा PPC_INST_PASTE_LAST            __PASTE(0, 0, 1, 1)

/* This defines the prefixed load/store inकाष्ठाions */
#अगर_घोषित __ASSEMBLY__
#  define stringअगरy_in_c(...)	__VA_ARGS__
#अन्यथा
#  define __stringअगरy_in_c(...)	#__VA_ARGS__
#  define stringअगरy_in_c(...)	__stringअगरy_in_c(__VA_ARGS__) " "
#पूर्ण_अगर

#घोषणा __PPC_RA(a)	(((a) & 0x1f) << 16)
#घोषणा __PPC_RS(s)	(((s) & 0x1f) << 21)
#घोषणा __PPC_RT(t)	__PPC_RS(t)
#घोषणा __PPC_PREFIX_R(r)	(((r) & 0x1) << 20)

#घोषणा PPC_PREFIX_MLS			0x06000000
#घोषणा PPC_PREFIX_8LS			0x04000000

#घोषणा PPC_INST_LBZ			0x88000000
#घोषणा PPC_INST_LHZ			0xa0000000
#घोषणा PPC_INST_LHA			0xa8000000
#घोषणा PPC_INST_LWZ			0x80000000
#घोषणा PPC_INST_STB			0x98000000
#घोषणा PPC_INST_STH			0xb0000000
#घोषणा PPC_INST_STW			0x90000000
#घोषणा PPC_INST_STD			0xf8000000
#घोषणा PPC_INST_LFS			0xc0000000
#घोषणा PPC_INST_LFD			0xc8000000
#घोषणा PPC_INST_STFS			0xd0000000
#घोषणा PPC_INST_STFD			0xd8000000

#घोषणा PREFIX_MLS(instr, t, a, r, d)	stringअगरy_in_c(.balign 64, , 4;)		\
					stringअगरy_in_c(.दीर्घ PPC_PREFIX_MLS |		\
						       __PPC_PREFIX_R(r) |		\
						       (((d) >> 16) & 0x3ffff);)	\
					stringअगरy_in_c(.दीर्घ (instr)  |			\
						       __PPC_RT(t) |			\
						       __PPC_RA(a) |			\
						       ((d) & 0xffff);\न)

#घोषणा PREFIX_8LS(instr, t, a, r, d)	stringअगरy_in_c(.balign 64, , 4;)		\
					stringअगरy_in_c(.दीर्घ PPC_PREFIX_8LS |		\
						       __PPC_PREFIX_R(r) |		\
						       (((d) >> 16) & 0x3ffff);)	\
					stringअगरy_in_c(.दीर्घ (instr)  |			\
						       __PPC_RT(t) |			\
						       __PPC_RA(a) |			\
						       ((d) & 0xffff);\न)

/* Prefixed Integer Load/Store inकाष्ठाions */
#घोषणा PLBZ(t, a, r, d)		PREFIX_MLS(PPC_INST_LBZ, t, a, r, d)
#घोषणा PLHZ(t, a, r, d)		PREFIX_MLS(PPC_INST_LHZ, t, a, r, d)
#घोषणा PLHA(t, a, r, d)		PREFIX_MLS(PPC_INST_LHA, t, a, r, d)
#घोषणा PLWZ(t, a, r, d)		PREFIX_MLS(PPC_INST_LWZ, t, a, r, d)
#घोषणा PLWA(t, a, r, d)		PREFIX_8LS(0xa4000000, t, a, r, d)
#घोषणा PLD(t, a, r, d)			PREFIX_8LS(0xe4000000, t, a, r, d)
#घोषणा PLQ(t, a, r, d)			PREFIX_8LS(0xe0000000, t, a, r, d)
#घोषणा PSTB(s, a, r, d)		PREFIX_MLS(PPC_INST_STB, s, a, r, d)
#घोषणा PSTH(s, a, r, d)		PREFIX_MLS(PPC_INST_STH, s, a, r, d)
#घोषणा PSTW(s, a, r, d)		PREFIX_MLS(PPC_INST_STW, s, a, r, d)
#घोषणा PSTD(s, a, r, d)		PREFIX_8LS(0xf4000000, s, a, r, d)
#घोषणा PSTQ(s, a, r, d)		PREFIX_8LS(0xf0000000, s, a, r, d)

/* Prefixed Floating-Poपूर्णांक Load/Store Inकाष्ठाions */
#घोषणा PLFS(frt, a, r, d)		PREFIX_MLS(PPC_INST_LFS, frt, a, r, d)
#घोषणा PLFD(frt, a, r, d)		PREFIX_MLS(PPC_INST_LFD, frt, a, r, d)
#घोषणा PSTFS(frs, a, r, d)		PREFIX_MLS(PPC_INST_STFS, frs, a, r, d)
#घोषणा PSTFD(frs, a, r, d)		PREFIX_MLS(PPC_INST_STFD, frs, a, r, d)

/* Prefixed VSX Load/Store Inकाष्ठाions */
#घोषणा PLXSD(vrt, a, r, d)		PREFIX_8LS(0xa8000000, vrt, a, r, d)
#घोषणा PLXSSP(vrt, a, r, d)		PREFIX_8LS(0xac000000, vrt, a, r, d)
#घोषणा PLXV0(s, a, r, d)		PREFIX_8LS(0xc8000000, s, a, r, d)
#घोषणा PLXV1(s, a, r, d)		PREFIX_8LS(0xcc000000, s, a, r, d)
#घोषणा PSTXSD(vrs, a, r, d)		PREFIX_8LS(0xb8000000, vrs, a, r, d)
#घोषणा PSTXSSP(vrs, a, r, d)		PREFIX_8LS(0xbc000000, vrs, a, r, d)
#घोषणा PSTXV0(s, a, r, d)		PREFIX_8LS(0xd8000000, s, a, r, d)
#घोषणा PSTXV1(s, a, r, d)		PREFIX_8LS(0xdc000000, s, a, r, d)

#पूर्ण_अगर /* _SELFTESTS_POWERPC_INSTRUCTIONS_H */
