<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Header क्रम the Gemini SATA bridge */
#अगर_अघोषित SATA_GEMINI_H
#घोषणा SATA_GEMINI_H

काष्ठा sata_gemini;

क्रमागत gemini_muxmode अणु
	GEMINI_MUXMODE_0 = 0,
	GEMINI_MUXMODE_1,
	GEMINI_MUXMODE_2,
	GEMINI_MUXMODE_3,
पूर्ण;

काष्ठा sata_gemini *gemini_sata_bridge_get(व्योम);
bool gemini_sata_bridge_enabled(काष्ठा sata_gemini *sg, bool is_ata1);
क्रमागत gemini_muxmode gemini_sata_get_muxmode(काष्ठा sata_gemini *sg);
पूर्णांक gemini_sata_start_bridge(काष्ठा sata_gemini *sg, अचिन्हित पूर्णांक bridge);
व्योम gemini_sata_stop_bridge(काष्ठा sata_gemini *sg, अचिन्हित पूर्णांक bridge);
पूर्णांक gemini_sata_reset_bridge(काष्ठा sata_gemini *sg, अचिन्हित पूर्णांक bridge);

#पूर्ण_अगर
