<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _LINUX_ATMBR2684_H
#घोषणा _LINUX_ATMBR2684_H

#समावेश <linux/types.h>
#समावेश <linux/aपंचांग.h>
#समावेश <linux/अगर.h>		/* For IFNAMSIZ */

/*
 * Type of media we're bridging (ethernet, token ring, etc)  Currently only
 * ethernet is supported
 */
#घोषणा BR2684_MEDIA_ETHERNET	(0)	/* 802.3 */
#घोषणा BR2684_MEDIA_802_4	(1)	/* 802.4 */
#घोषणा BR2684_MEDIA_TR		(2)	/* 802.5 - token ring */
#घोषणा BR2684_MEDIA_FDDI	(3)
#घोषणा BR2684_MEDIA_802_6	(4)	/* 802.6 */

					/* used only at device creation:  */
#घोषणा BR2684_FLAG_ROUTED	(1<<16)	/* payload is routed, not bridged */

/*
 * Is there FCS inbound on this VC?  This currently isn't supported.
 */
#घोषणा BR2684_FCSIN_NO		(0)
#घोषणा BR2684_FCSIN_IGNORE	(1)
#घोषणा BR2684_FCSIN_VERIFY	(2)

/*
 * Is there FCS outbound on this VC?  This currently isn't supported.
 */
#घोषणा BR2684_FCSOUT_NO	(0)
#घोषणा BR2684_FCSOUT_SENDZERO	(1)
#घोषणा BR2684_FCSOUT_GENERATE	(2)

/*
 * Does this VC include LLC encapsulation?
 */
#घोषणा BR2684_ENCAPS_VC	(0)	/* VC-mux */
#घोषणा BR2684_ENCAPS_LLC	(1)
#घोषणा BR2684_ENCAPS_AUTODETECT (2)	/* Unsuported */

/*
 * Is this VC bridged or routed?
 */

#घोषणा BR2684_PAYLOAD_ROUTED   (0)
#घोषणा BR2684_PAYLOAD_BRIDGED  (1)

/*
 * This is क्रम the ATM_NEWBACKENDIF call - these are like socket families:
 * the first element of the काष्ठाure is the backend number and the rest
 * is per-backend specअगरic
 */
काष्ठा aपंचांग_newअगर_br2684 अणु
	aपंचांग_backend_t backend_num;	/* ATM_BACKEND_BR2684 */
	पूर्णांक media;		/* BR2684_MEDIA_*, flags in upper bits */
	अक्षर अगरname[IFNAMSIZ];
	पूर्णांक mtu;
पूर्ण;

/*
 * This काष्ठाure is used to specअगरy a br2684 पूर्णांकerface - either by a
 * positive पूर्णांकeger (वापसed by ATM_NEWBACKENDIF) or the पूर्णांकerfaces name
 */
#घोषणा BR2684_FIND_BYNOTHING	(0)
#घोषणा BR2684_FIND_BYNUM	(1)
#घोषणा BR2684_FIND_BYIFNAME	(2)
काष्ठा br2684_अगर_spec अणु
	पूर्णांक method;		/* BR2684_FIND_* */
	जोड़ अणु
		अक्षर अगरname[IFNAMSIZ];
		पूर्णांक devnum;
	पूर्ण spec;
पूर्ण;

/*
 * This is क्रम the ATM_SETBACKEND call - these are like socket families:
 * the first element of the काष्ठाure is the backend number and the rest
 * is per-backend specअगरic
 */
काष्ठा aपंचांग_backend_br2684 अणु
	aपंचांग_backend_t backend_num;	/* ATM_BACKEND_BR2684 */
	काष्ठा br2684_अगर_spec अगरspec;
	पूर्णांक fcs_in;		/* BR2684_FCSIN_* */
	पूर्णांक fcs_out;		/* BR2684_FCSOUT_* */
	पूर्णांक fcs_स्वतः;		/* 1: fcs_अणुin,outपूर्ण disabled अगर no FCS rx'ed */
	पूर्णांक encaps;		/* BR2684_ENCAPS_* */
	पूर्णांक has_vpiid;		/* 1: use vpn_id - Unsupported */
	__u8 vpn_id[7];
	पूर्णांक send_padding;	/* unsupported */
	पूर्णांक min_size;		/* we will pad smaller packets than this */
पूर्ण;

/*
 * The BR2684_SETFILT ioctl is an experimental mechanism क्रम folks
 * terminating a large number of IP-only vcc's.  When netfilter allows
 * efficient per-अगर in/out filters, this support will be हटाओd
 */
काष्ठा br2684_filter अणु
	__be32 prefix;		/* network byte order */
	__be32 neपंचांगask;		/* 0 = disable filter */
पूर्ण;

काष्ठा br2684_filter_set अणु
	काष्ठा br2684_अगर_spec अगरspec;
	काष्ठा br2684_filter filter;
पूर्ण;

क्रमागत br2684_payload अणु
	p_routed = BR2684_PAYLOAD_ROUTED,
	p_bridged = BR2684_PAYLOAD_BRIDGED,
पूर्ण;

#घोषणा BR2684_SETFILT	_IOW( 'a', ATMIOC_BACKEND + 0, \
				काष्ठा br2684_filter_set)

#पूर्ण_अगर /* _LINUX_ATMBR2684_H */
