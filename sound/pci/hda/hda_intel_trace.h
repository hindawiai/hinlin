<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM hda_पूर्णांकel
#घोषणा TRACE_INCLUDE_खाता hda_पूर्णांकel_trace

#अगर !defined(_TRACE_HDA_INTEL_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_HDA_INTEL_H

#समावेश <linux/tracepoपूर्णांक.h>

DECLARE_EVENT_CLASS(hda_pm,
	TP_PROTO(काष्ठा azx *chip),

	TP_ARGS(chip),

	TP_STRUCT__entry(
		__field(पूर्णांक, dev_index)
	),

	TP_fast_assign(
		__entry->dev_index = (chip)->dev_index;
	),

	TP_prपूर्णांकk("card index: %d", __entry->dev_index)
);

DEFINE_EVENT(hda_pm, azx_suspend,
	TP_PROTO(काष्ठा azx *chip),
	TP_ARGS(chip)
);

DEFINE_EVENT(hda_pm, azx_resume,
	TP_PROTO(काष्ठा azx *chip),
	TP_ARGS(chip)
);

#अगर_घोषित CONFIG_PM
DEFINE_EVENT(hda_pm, azx_runसमय_suspend,
	TP_PROTO(काष्ठा azx *chip),
	TP_ARGS(chip)
);

DEFINE_EVENT(hda_pm, azx_runसमय_resume,
	TP_PROTO(काष्ठा azx *chip),
	TP_ARGS(chip)
);
#पूर्ण_अगर

#पूर्ण_अगर /* _TRACE_HDA_INTEL_H */

/* This part must be outside protection */
#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#समावेश <trace/define_trace.h>
