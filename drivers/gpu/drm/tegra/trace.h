<शैली गुरु>
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM tegra

#अगर !defined(DRM_TEGRA_TRACE_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा DRM_TEGRA_TRACE_H 1

#समावेश <linux/device.h>
#समावेश <linux/tracepoपूर्णांक.h>

DECLARE_EVENT_CLASS(रेजिस्टर_access,
	TP_PROTO(काष्ठा device *dev, अचिन्हित पूर्णांक offset, u32 value),
	TP_ARGS(dev, offset, value),
	TP_STRUCT__entry(
		__field(काष्ठा device *, dev)
		__field(अचिन्हित पूर्णांक, offset)
		__field(u32, value)
	),
	TP_fast_assign(
		__entry->dev = dev;
		__entry->offset = offset;
		__entry->value = value;
	),
	TP_prपूर्णांकk("%s %04x %08x", dev_name(__entry->dev), __entry->offset,
		  __entry->value)
);

DEFINE_EVENT(रेजिस्टर_access, dc_ग_लिखोl,
	TP_PROTO(काष्ठा device *dev, अचिन्हित पूर्णांक offset, u32 value),
	TP_ARGS(dev, offset, value));
DEFINE_EVENT(रेजिस्टर_access, dc_पढ़ोl,
	TP_PROTO(काष्ठा device *dev, अचिन्हित पूर्णांक offset, u32 value),
	TP_ARGS(dev, offset, value));

DEFINE_EVENT(रेजिस्टर_access, hdmi_ग_लिखोl,
	TP_PROTO(काष्ठा device *dev, अचिन्हित पूर्णांक offset, u32 value),
	TP_ARGS(dev, offset, value));
DEFINE_EVENT(रेजिस्टर_access, hdmi_पढ़ोl,
	TP_PROTO(काष्ठा device *dev, अचिन्हित पूर्णांक offset, u32 value),
	TP_ARGS(dev, offset, value));

DEFINE_EVENT(रेजिस्टर_access, dsi_ग_लिखोl,
	TP_PROTO(काष्ठा device *dev, अचिन्हित पूर्णांक offset, u32 value),
	TP_ARGS(dev, offset, value));
DEFINE_EVENT(रेजिस्टर_access, dsi_पढ़ोl,
	TP_PROTO(काष्ठा device *dev, अचिन्हित पूर्णांक offset, u32 value),
	TP_ARGS(dev, offset, value));

DEFINE_EVENT(रेजिस्टर_access, dpaux_ग_लिखोl,
	TP_PROTO(काष्ठा device *dev, अचिन्हित पूर्णांक offset, u32 value),
	TP_ARGS(dev, offset, value));
DEFINE_EVENT(रेजिस्टर_access, dpaux_पढ़ोl,
	TP_PROTO(काष्ठा device *dev, अचिन्हित पूर्णांक offset, u32 value),
	TP_ARGS(dev, offset, value));

DEFINE_EVENT(रेजिस्टर_access, sor_ग_लिखोl,
	TP_PROTO(काष्ठा device *dev, अचिन्हित पूर्णांक offset, u32 value),
	TP_ARGS(dev, offset, value));
DEFINE_EVENT(रेजिस्टर_access, sor_पढ़ोl,
	TP_PROTO(काष्ठा device *dev, अचिन्हित पूर्णांक offset, u32 value),
	TP_ARGS(dev, offset, value));

#पूर्ण_अगर /* DRM_TEGRA_TRACE_H */

/* This part must be outside protection */
#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH ../../drivers/gpu/drm/tegra
#घोषणा TRACE_INCLUDE_खाता trace
#समावेश <trace/define_trace.h>
