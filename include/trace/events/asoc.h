<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM asoc

#अगर !defined(_TRACE_ASOC_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_ASOC_H

#समावेश <linux/kसमय.स>
#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <sound/jack.h>

#घोषणा DAPM_सूचीECT "(direct)"
#घोषणा DAPM_ARROW(dir) (((dir) == SND_SOC_DAPM_सूची_OUT) ? "->" : "<-")

काष्ठा snd_soc_jack;
काष्ठा snd_soc_card;
काष्ठा snd_soc_dapm_widget;
काष्ठा snd_soc_dapm_path;

DECLARE_EVENT_CLASS(snd_soc_card,

	TP_PROTO(काष्ठा snd_soc_card *card, पूर्णांक val),

	TP_ARGS(card, val),

	TP_STRUCT__entry(
		__string(	name,		card->name	)
		__field(	पूर्णांक,		val		)
	),

	TP_fast_assign(
		__assign_str(name, card->name);
		__entry->val = val;
	),

	TP_prपूर्णांकk("card=%s val=%d", __get_str(name), (पूर्णांक)__entry->val)
);

DEFINE_EVENT(snd_soc_card, snd_soc_bias_level_start,

	TP_PROTO(काष्ठा snd_soc_card *card, पूर्णांक val),

	TP_ARGS(card, val)

);

DEFINE_EVENT(snd_soc_card, snd_soc_bias_level_करोne,

	TP_PROTO(काष्ठा snd_soc_card *card, पूर्णांक val),

	TP_ARGS(card, val)

);

DECLARE_EVENT_CLASS(snd_soc_dapm_basic,

	TP_PROTO(काष्ठा snd_soc_card *card),

	TP_ARGS(card),

	TP_STRUCT__entry(
		__string(	name,	card->name	)
	),

	TP_fast_assign(
		__assign_str(name, card->name);
	),

	TP_prपूर्णांकk("card=%s", __get_str(name))
);

DEFINE_EVENT(snd_soc_dapm_basic, snd_soc_dapm_start,

	TP_PROTO(काष्ठा snd_soc_card *card),

	TP_ARGS(card)

);

DEFINE_EVENT(snd_soc_dapm_basic, snd_soc_dapm_करोne,

	TP_PROTO(काष्ठा snd_soc_card *card),

	TP_ARGS(card)

);

DECLARE_EVENT_CLASS(snd_soc_dapm_widget,

	TP_PROTO(काष्ठा snd_soc_dapm_widget *w, पूर्णांक val),

	TP_ARGS(w, val),

	TP_STRUCT__entry(
		__string(	name,	w->name		)
		__field(	पूर्णांक,	val		)
	),

	TP_fast_assign(
		__assign_str(name, w->name);
		__entry->val = val;
	),

	TP_prपूर्णांकk("widget=%s val=%d", __get_str(name),
		  (पूर्णांक)__entry->val)
);

DEFINE_EVENT(snd_soc_dapm_widget, snd_soc_dapm_widget_घातer,

	TP_PROTO(काष्ठा snd_soc_dapm_widget *w, पूर्णांक val),

	TP_ARGS(w, val)

);

DEFINE_EVENT(snd_soc_dapm_widget, snd_soc_dapm_widget_event_start,

	TP_PROTO(काष्ठा snd_soc_dapm_widget *w, पूर्णांक val),

	TP_ARGS(w, val)

);

DEFINE_EVENT(snd_soc_dapm_widget, snd_soc_dapm_widget_event_करोne,

	TP_PROTO(काष्ठा snd_soc_dapm_widget *w, पूर्णांक val),

	TP_ARGS(w, val)

);

TRACE_EVENT(snd_soc_dapm_walk_करोne,

	TP_PROTO(काष्ठा snd_soc_card *card),

	TP_ARGS(card),

	TP_STRUCT__entry(
		__string(	name,	card->name		)
		__field(	पूर्णांक,	घातer_checks		)
		__field(	पूर्णांक,	path_checks		)
		__field(	पूर्णांक,	neighbour_checks	)
	),

	TP_fast_assign(
		__assign_str(name, card->name);
		__entry->घातer_checks = card->dapm_stats.घातer_checks;
		__entry->path_checks = card->dapm_stats.path_checks;
		__entry->neighbour_checks = card->dapm_stats.neighbour_checks;
	),

	TP_prपूर्णांकk("%s: checks %d power, %d path, %d neighbour",
		  __get_str(name), (पूर्णांक)__entry->घातer_checks,
		  (पूर्णांक)__entry->path_checks, (पूर्णांक)__entry->neighbour_checks)
);

TRACE_EVENT(snd_soc_dapm_path,

	TP_PROTO(काष्ठा snd_soc_dapm_widget *widget,
		क्रमागत snd_soc_dapm_direction dir,
		काष्ठा snd_soc_dapm_path *path),

	TP_ARGS(widget, dir, path),

	TP_STRUCT__entry(
		__string(	wname,	widget->name		)
		__string(	pname,	path->name ? path->name : DAPM_सूचीECT)
		__string(	pnname,	path->node[dir]->name	)
		__field(	पूर्णांक,	path_node		)
		__field(	पूर्णांक,	path_connect		)
		__field(	पूर्णांक,	path_dir		)
	),

	TP_fast_assign(
		__assign_str(wname, widget->name);
		__assign_str(pname, path->name ? path->name : DAPM_सूचीECT);
		__assign_str(pnname, path->node[dir]->name);
		__entry->path_connect = path->connect;
		__entry->path_node = (दीर्घ)path->node[dir];
		__entry->path_dir = dir;
	),

	TP_prपूर्णांकk("%c%s %s %s %s %s",
		(पूर्णांक) __entry->path_node &&
		(पूर्णांक) __entry->path_connect ? '*' : ' ',
		__get_str(wname), DAPM_ARROW(__entry->path_dir),
		__get_str(pname), DAPM_ARROW(__entry->path_dir),
		__get_str(pnname))
);

TRACE_EVENT(snd_soc_dapm_connected,

	TP_PROTO(पूर्णांक paths, पूर्णांक stream),

	TP_ARGS(paths, stream),

	TP_STRUCT__entry(
		__field(	पूर्णांक,	paths		)
		__field(	पूर्णांक,	stream		)
	),

	TP_fast_assign(
		__entry->paths = paths;
		__entry->stream = stream;
	),

	TP_prपूर्णांकk("%s: found %d paths",
		__entry->stream ? "capture" : "playback", __entry->paths)
);

TRACE_EVENT(snd_soc_jack_irq,

	TP_PROTO(स्थिर अक्षर *name),

	TP_ARGS(name),

	TP_STRUCT__entry(
		__string(	name,	name		)
	),

	TP_fast_assign(
		__assign_str(name, name);
	),

	TP_prपूर्णांकk("%s", __get_str(name))
);

TRACE_EVENT(snd_soc_jack_report,

	TP_PROTO(काष्ठा snd_soc_jack *jack, पूर्णांक mask, पूर्णांक val),

	TP_ARGS(jack, mask, val),

	TP_STRUCT__entry(
		__string(	name,		jack->jack->id		)
		__field(	पूर्णांक,		mask			)
		__field(	पूर्णांक,		val			)
	),

	TP_fast_assign(
		__assign_str(name, jack->jack->id);
		__entry->mask = mask;
		__entry->val = val;
	),

	TP_prपूर्णांकk("jack=%s %x/%x", __get_str(name), (पूर्णांक)__entry->val,
		  (पूर्णांक)__entry->mask)
);

TRACE_EVENT(snd_soc_jack_notअगरy,

	TP_PROTO(काष्ठा snd_soc_jack *jack, पूर्णांक val),

	TP_ARGS(jack, val),

	TP_STRUCT__entry(
		__string(	name,		jack->jack->id		)
		__field(	पूर्णांक,		val			)
	),

	TP_fast_assign(
		__assign_str(name, jack->jack->id);
		__entry->val = val;
	),

	TP_prपूर्णांकk("jack=%s %x", __get_str(name), (पूर्णांक)__entry->val)
);

#पूर्ण_अगर /* _TRACE_ASOC_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
