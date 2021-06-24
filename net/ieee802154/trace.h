<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Based on net/wireless/trace.h */

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM cfg802154

#अगर !defined(__RDEV_CFG802154_OPS_TRACE) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा __RDEV_CFG802154_OPS_TRACE

#समावेश <linux/tracepoपूर्णांक.h>

#समावेश <net/cfg802154.h>

#घोषणा MAXNAME		32
#घोषणा WPAN_PHY_ENTRY	__array(अक्षर, wpan_phy_name, MAXNAME)
#घोषणा WPAN_PHY_ASSIGN	strlcpy(__entry->wpan_phy_name,	 \
				wpan_phy_name(wpan_phy), \
				MAXNAME)
#घोषणा WPAN_PHY_PR_FMT	"%s"
#घोषणा WPAN_PHY_PR_ARG	__entry->wpan_phy_name

#घोषणा WPAN_DEV_ENTRY	__field(u32, identअगरier)
#घोषणा WPAN_DEV_ASSIGN	(__entry->identअगरier) = (!IS_ERR_OR_शून्य(wpan_dev) \
					 ? wpan_dev->identअगरier : 0)
#घोषणा WPAN_DEV_PR_FMT	"wpan_dev(%u)"
#घोषणा WPAN_DEV_PR_ARG	(__entry->identअगरier)

#घोषणा WPAN_CCA_ENTRY	__field(क्रमागत nl802154_cca_modes, cca_mode) \
			__field(क्रमागत nl802154_cca_opts, cca_opt)
#घोषणा WPAN_CCA_ASSIGN \
	करो अणु					 \
		(__entry->cca_mode) = cca->mode; \
		(__entry->cca_opt) = cca->opt;	 \
	पूर्ण जबतक (0)
#घोषणा WPAN_CCA_PR_FMT	"cca_mode: %d, cca_opt: %d"
#घोषणा WPAN_CCA_PR_ARG __entry->cca_mode, __entry->cca_opt

#घोषणा BOOL_TO_STR(bo) (bo) ? "true" : "false"

/*************************************************************
 *			rdev->ops traces		     *
 *************************************************************/

DECLARE_EVENT_CLASS(wpan_phy_only_evt,
	TP_PROTO(काष्ठा wpan_phy *wpan_phy),
	TP_ARGS(wpan_phy),
	TP_STRUCT__entry(
		WPAN_PHY_ENTRY
	),
	TP_fast_assign(
		WPAN_PHY_ASSIGN;
	),
	TP_prपूर्णांकk(WPAN_PHY_PR_FMT, WPAN_PHY_PR_ARG)
);

DEFINE_EVENT(wpan_phy_only_evt, 802154_rdev_suspend,
	TP_PROTO(काष्ठा wpan_phy *wpan_phy),
	TP_ARGS(wpan_phy)
);

DEFINE_EVENT(wpan_phy_only_evt, 802154_rdev_resume,
	TP_PROTO(काष्ठा wpan_phy *wpan_phy),
	TP_ARGS(wpan_phy)
);

TRACE_EVENT(802154_rdev_add_भव_पूर्णांकf,
	TP_PROTO(काष्ठा wpan_phy *wpan_phy, अक्षर *name,
		 क्रमागत nl802154_अगरtype type, __le64 extended_addr),
	TP_ARGS(wpan_phy, name, type, extended_addr),
	TP_STRUCT__entry(
		WPAN_PHY_ENTRY
		__string(vir_पूर्णांकf_name, name ? name : "<noname>")
		__field(क्रमागत nl802154_अगरtype, type)
		__field(__le64, extended_addr)
	),
	TP_fast_assign(
		WPAN_PHY_ASSIGN;
		__assign_str(vir_पूर्णांकf_name, name ? name : "<noname>");
		__entry->type = type;
		__entry->extended_addr = extended_addr;
	),
	TP_prपूर्णांकk(WPAN_PHY_PR_FMT ", virtual intf name: %s, type: %d, extended addr: 0x%llx",
		  WPAN_PHY_PR_ARG, __get_str(vir_पूर्णांकf_name), __entry->type,
		  __le64_to_cpu(__entry->extended_addr))
);

TRACE_EVENT(802154_rdev_del_भव_पूर्णांकf,
	TP_PROTO(काष्ठा wpan_phy *wpan_phy, काष्ठा wpan_dev *wpan_dev),
	TP_ARGS(wpan_phy, wpan_dev),
	TP_STRUCT__entry(
		WPAN_PHY_ENTRY
		WPAN_DEV_ENTRY
	),
	TP_fast_assign(
		WPAN_PHY_ASSIGN;
		WPAN_DEV_ASSIGN;
	),
	TP_prपूर्णांकk(WPAN_PHY_PR_FMT ", " WPAN_DEV_PR_FMT, WPAN_PHY_PR_ARG,
		  WPAN_DEV_PR_ARG)
);

TRACE_EVENT(802154_rdev_set_channel,
	TP_PROTO(काष्ठा wpan_phy *wpan_phy, u8 page, u8 channel),
	TP_ARGS(wpan_phy, page, channel),
	TP_STRUCT__entry(
		WPAN_PHY_ENTRY
		__field(u8, page)
		__field(u8, channel)
	),
	TP_fast_assign(
		WPAN_PHY_ASSIGN;
		__entry->page = page;
		__entry->channel = channel;
	),
	TP_prपूर्णांकk(WPAN_PHY_PR_FMT ", page: %d, channel: %d", WPAN_PHY_PR_ARG,
		  __entry->page, __entry->channel)
);

TRACE_EVENT(802154_rdev_set_tx_घातer,
	TP_PROTO(काष्ठा wpan_phy *wpan_phy, s32 घातer),
	TP_ARGS(wpan_phy, घातer),
	TP_STRUCT__entry(
		WPAN_PHY_ENTRY
		__field(s32, घातer)
	),
	TP_fast_assign(
		WPAN_PHY_ASSIGN;
		__entry->घातer = घातer;
	),
	TP_prपूर्णांकk(WPAN_PHY_PR_FMT ", mbm: %d", WPAN_PHY_PR_ARG,
		  __entry->घातer)
);

TRACE_EVENT(802154_rdev_set_cca_mode,
	TP_PROTO(काष्ठा wpan_phy *wpan_phy, स्थिर काष्ठा wpan_phy_cca *cca),
	TP_ARGS(wpan_phy, cca),
	TP_STRUCT__entry(
		WPAN_PHY_ENTRY
		WPAN_CCA_ENTRY
	),
	TP_fast_assign(
		WPAN_PHY_ASSIGN;
		WPAN_CCA_ASSIGN;
	),
	TP_prपूर्णांकk(WPAN_PHY_PR_FMT ", " WPAN_CCA_PR_FMT, WPAN_PHY_PR_ARG,
		  WPAN_CCA_PR_ARG)
);

TRACE_EVENT(802154_rdev_set_cca_ed_level,
	TP_PROTO(काष्ठा wpan_phy *wpan_phy, s32 ed_level),
	TP_ARGS(wpan_phy, ed_level),
	TP_STRUCT__entry(
		WPAN_PHY_ENTRY
		__field(s32, ed_level)
	),
	TP_fast_assign(
		WPAN_PHY_ASSIGN;
		__entry->ed_level = ed_level;
	),
	TP_prपूर्णांकk(WPAN_PHY_PR_FMT ", ed level: %d", WPAN_PHY_PR_ARG,
		  __entry->ed_level)
);

DECLARE_EVENT_CLASS(802154_le16_ढाँचा,
	TP_PROTO(काष्ठा wpan_phy *wpan_phy, काष्ठा wpan_dev *wpan_dev,
		 __le16 le16arg),
	TP_ARGS(wpan_phy, wpan_dev, le16arg),
	TP_STRUCT__entry(
		WPAN_PHY_ENTRY
		WPAN_DEV_ENTRY
		__field(__le16, le16arg)
	),
	TP_fast_assign(
		WPAN_PHY_ASSIGN;
		WPAN_DEV_ASSIGN;
		__entry->le16arg = le16arg;
	),
	TP_prपूर्णांकk(WPAN_PHY_PR_FMT ", " WPAN_DEV_PR_FMT ", pan id: 0x%04x",
		  WPAN_PHY_PR_ARG, WPAN_DEV_PR_ARG,
		  __le16_to_cpu(__entry->le16arg))
);

DEFINE_EVENT(802154_le16_ढाँचा, 802154_rdev_set_pan_id,
	TP_PROTO(काष्ठा wpan_phy *wpan_phy, काष्ठा wpan_dev *wpan_dev,
		 __le16 le16arg),
	TP_ARGS(wpan_phy, wpan_dev, le16arg)
);

DEFINE_EVENT_PRINT(802154_le16_ढाँचा, 802154_rdev_set_लघु_addr,
	TP_PROTO(काष्ठा wpan_phy *wpan_phy, काष्ठा wpan_dev *wpan_dev,
		 __le16 le16arg),
	TP_ARGS(wpan_phy, wpan_dev, le16arg),
	TP_prपूर्णांकk(WPAN_PHY_PR_FMT ", " WPAN_DEV_PR_FMT ", short addr: 0x%04x",
		  WPAN_PHY_PR_ARG, WPAN_DEV_PR_ARG,
		  __le16_to_cpu(__entry->le16arg))
);

TRACE_EVENT(802154_rdev_set_backoff_exponent,
	TP_PROTO(काष्ठा wpan_phy *wpan_phy, काष्ठा wpan_dev *wpan_dev,
		 u8 min_be, u8 max_be),
	TP_ARGS(wpan_phy, wpan_dev, min_be, max_be),
	TP_STRUCT__entry(
		WPAN_PHY_ENTRY
		WPAN_DEV_ENTRY
		__field(u8, min_be)
		__field(u8, max_be)
	),
	TP_fast_assign(
		WPAN_PHY_ASSIGN;
		WPAN_DEV_ASSIGN;
		__entry->min_be = min_be;
		__entry->max_be = max_be;
	),

	TP_prपूर्णांकk(WPAN_PHY_PR_FMT ", " WPAN_DEV_PR_FMT
		  ", min be: %d, max be: %d", WPAN_PHY_PR_ARG,
		  WPAN_DEV_PR_ARG, __entry->min_be, __entry->max_be)
);

TRACE_EVENT(802154_rdev_set_csma_backoffs,
	TP_PROTO(काष्ठा wpan_phy *wpan_phy, काष्ठा wpan_dev *wpan_dev,
		 u8 max_csma_backoffs),
	TP_ARGS(wpan_phy, wpan_dev, max_csma_backoffs),
	TP_STRUCT__entry(
		WPAN_PHY_ENTRY
		WPAN_DEV_ENTRY
		__field(u8, max_csma_backoffs)
	),
	TP_fast_assign(
		WPAN_PHY_ASSIGN;
		WPAN_DEV_ASSIGN;
		__entry->max_csma_backoffs = max_csma_backoffs;
	),

	TP_prपूर्णांकk(WPAN_PHY_PR_FMT ", " WPAN_DEV_PR_FMT
		  ", max csma backoffs: %d", WPAN_PHY_PR_ARG,
		  WPAN_DEV_PR_ARG, __entry->max_csma_backoffs)
);

TRACE_EVENT(802154_rdev_set_max_frame_retries,
	TP_PROTO(काष्ठा wpan_phy *wpan_phy, काष्ठा wpan_dev *wpan_dev,
		 s8 max_frame_retries),
	TP_ARGS(wpan_phy, wpan_dev, max_frame_retries),
	TP_STRUCT__entry(
		WPAN_PHY_ENTRY
		WPAN_DEV_ENTRY
		__field(s8, max_frame_retries)
	),
	TP_fast_assign(
		WPAN_PHY_ASSIGN;
		WPAN_DEV_ASSIGN;
		__entry->max_frame_retries = max_frame_retries;
	),

	TP_prपूर्णांकk(WPAN_PHY_PR_FMT ", " WPAN_DEV_PR_FMT
		  ", max frame retries: %d", WPAN_PHY_PR_ARG,
		  WPAN_DEV_PR_ARG, __entry->max_frame_retries)
);

TRACE_EVENT(802154_rdev_set_lbt_mode,
	TP_PROTO(काष्ठा wpan_phy *wpan_phy, काष्ठा wpan_dev *wpan_dev,
		 bool mode),
	TP_ARGS(wpan_phy, wpan_dev, mode),
	TP_STRUCT__entry(
		WPAN_PHY_ENTRY
		WPAN_DEV_ENTRY
		__field(bool, mode)
	),
	TP_fast_assign(
		WPAN_PHY_ASSIGN;
		WPAN_DEV_ASSIGN;
		__entry->mode = mode;
	),
	TP_prपूर्णांकk(WPAN_PHY_PR_FMT ", " WPAN_DEV_PR_FMT
		", lbt mode: %s", WPAN_PHY_PR_ARG,
		WPAN_DEV_PR_ARG, BOOL_TO_STR(__entry->mode))
);

TRACE_EVENT(802154_rdev_set_ackreq_शेष,
	TP_PROTO(काष्ठा wpan_phy *wpan_phy, काष्ठा wpan_dev *wpan_dev,
		 bool ackreq),
	TP_ARGS(wpan_phy, wpan_dev, ackreq),
	TP_STRUCT__entry(
		WPAN_PHY_ENTRY
		WPAN_DEV_ENTRY
		__field(bool, ackreq)
	),
	TP_fast_assign(
		WPAN_PHY_ASSIGN;
		WPAN_DEV_ASSIGN;
		__entry->ackreq = ackreq;
	),
	TP_prपूर्णांकk(WPAN_PHY_PR_FMT ", " WPAN_DEV_PR_FMT
		", ackreq default: %s", WPAN_PHY_PR_ARG,
		WPAN_DEV_PR_ARG, BOOL_TO_STR(__entry->ackreq))
);

TRACE_EVENT(802154_rdev_वापस_पूर्णांक,
	TP_PROTO(काष्ठा wpan_phy *wpan_phy, पूर्णांक ret),
	TP_ARGS(wpan_phy, ret),
	TP_STRUCT__entry(
		WPAN_PHY_ENTRY
		__field(पूर्णांक, ret)
	),
	TP_fast_assign(
		WPAN_PHY_ASSIGN;
		__entry->ret = ret;
	),
	TP_prपूर्णांकk(WPAN_PHY_PR_FMT ", returned: %d", WPAN_PHY_PR_ARG,
		  __entry->ret)
);

#पूर्ण_अगर /* !__RDEV_CFG802154_OPS_TRACE || TRACE_HEADER_MULTI_READ */

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता trace
#समावेश <trace/define_trace.h>
