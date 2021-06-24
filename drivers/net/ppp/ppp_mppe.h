<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#घोषणा MPPE_PAD                4      /* MPPE growth per frame */
#घोषणा MPPE_MAX_KEY_LEN       16      /* largest key length (128-bit) */

/* option bits क्रम ccp_options.mppe */
#घोषणा MPPE_OPT_40            0x01    /* 40 bit */
#घोषणा MPPE_OPT_128           0x02    /* 128 bit */
#घोषणा MPPE_OPT_STATEFUL      0x04    /* stateful mode */
/* unsupported opts */
#घोषणा MPPE_OPT_56            0x08    /* 56 bit */
#घोषणा MPPE_OPT_MPPC          0x10    /* MPPC compression */
#घोषणा MPPE_OPT_D             0x20    /* Unknown */
#घोषणा MPPE_OPT_UNSUPPORTED (MPPE_OPT_56|MPPE_OPT_MPPC|MPPE_OPT_D)
#घोषणा MPPE_OPT_UNKNOWN       0x40    /* Bits !defined in RFC 3078 were set */

/*
 * This is not nice ... the alternative is a bitfield काष्ठा though.
 * And unक्रमtunately, we cannot share the same bits क्रम the option
 * names above since C and H are the same bit.  We could करो a u_पूर्णांक32
 * but then we have to करो a htonl() all the समय and/or we still need
 * to know which octet is which.
 */
#घोषणा MPPE_C_BIT             0x01    /* MPPC */
#घोषणा MPPE_D_BIT             0x10    /* Obsolete, usage unknown */
#घोषणा MPPE_L_BIT             0x20    /* 40-bit */
#घोषणा MPPE_S_BIT             0x40    /* 128-bit */
#घोषणा MPPE_M_BIT             0x80    /* 56-bit, not supported */
#घोषणा MPPE_H_BIT             0x01    /* Stateless (in a dअगरferent byte) */

/* Does not include H bit; used क्रम least signअगरicant octet only. */
#घोषणा MPPE_ALL_BITS (MPPE_D_BIT|MPPE_L_BIT|MPPE_S_BIT|MPPE_M_BIT|MPPE_H_BIT)

/* Build a CI from mppe opts (see RFC 3078) */
#घोषणा MPPE_OPTS_TO_CI(opts, ci)              \
    करो अणु                                       \
       u_अक्षर *ptr = ci; /* u_अक्षर[4] */       \
                                               \
       /* H bit */                             \
       अगर (opts & MPPE_OPT_STATEFUL)           \
           *ptr++ = 0x0;                       \
       अन्यथा                                    \
           *ptr++ = MPPE_H_BIT;                \
       *ptr++ = 0;                             \
       *ptr++ = 0;                             \
                                               \
       /* S,L bits */                          \
       *ptr = 0;                               \
       अगर (opts & MPPE_OPT_128)                \
           *ptr |= MPPE_S_BIT;                 \
       अगर (opts & MPPE_OPT_40)                 \
           *ptr |= MPPE_L_BIT;                 \
       /* M,D,C bits not supported */          \
    पूर्ण जबतक (/* CONSTCOND */ 0)

/* The reverse of the above */
#घोषणा MPPE_CI_TO_OPTS(ci, opts)              \
    करो अणु                                       \
       u_अक्षर *ptr = ci; /* u_अक्षर[4] */       \
                                               \
       opts = 0;                               \
                                               \
       /* H bit */                             \
       अगर (!(ptr[0] & MPPE_H_BIT))             \
           opts |= MPPE_OPT_STATEFUL;          \
                                               \
       /* S,L bits */                          \
       अगर (ptr[3] & MPPE_S_BIT)                \
           opts |= MPPE_OPT_128;               \
       अगर (ptr[3] & MPPE_L_BIT)                \
           opts |= MPPE_OPT_40;                \
                                               \
       /* M,D,C bits */                        \
       अगर (ptr[3] & MPPE_M_BIT)                \
           opts |= MPPE_OPT_56;                \
       अगर (ptr[3] & MPPE_D_BIT)                \
           opts |= MPPE_OPT_D;                 \
       अगर (ptr[3] & MPPE_C_BIT)                \
           opts |= MPPE_OPT_MPPC;              \
                                               \
       /* Other bits */                        \
       अगर (ptr[0] & ~MPPE_H_BIT)               \
           opts |= MPPE_OPT_UNKNOWN;           \
       अगर (ptr[1] || ptr[2])                   \
           opts |= MPPE_OPT_UNKNOWN;           \
       अगर (ptr[3] & ~MPPE_ALL_BITS)            \
           opts |= MPPE_OPT_UNKNOWN;           \
    पूर्ण जबतक (/* CONSTCOND */ 0)
