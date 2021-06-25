<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2015 Intel Corporation
 */

#अगर_अघोषित INTEL_MOCS_H
#घोषणा INTEL_MOCS_H

/**
 * DOC: Memory Objects Control State (MOCS)
 *
 * Motivation:
 * In previous Gens the MOCS settings was a value that was set by user land as
 * part of the batch. In Gen9 this has changed to be a single table (per ring)
 * that all batches now reference by index instead of programming the MOCS
 * directly.
 *
 * The one wrinkle in this is that only PART of the MOCS tables are included
 * in context (The GFX_MOCS_0 - GFX_MOCS_64 and the LNCFCMOCS0 - LNCFCMOCS32
 * रेजिस्टरs). The rest are not (the settings क्रम the other rings).
 *
 * This table needs to be set at प्रणाली start-up because the way the table
 * पूर्णांकeracts with the contexts and the GmmLib पूर्णांकerface.
 *
 *
 * Implementation:
 *
 * The tables (one per supported platक्रमm) are defined in पूर्णांकel_mocs.c
 * and are programmed in the first batch after the context is loaded
 * (with the hardware workarounds). This will then let the usual
 * context handling keep the MOCS in step.
 */

काष्ठा पूर्णांकel_engine_cs;
काष्ठा पूर्णांकel_gt;

व्योम पूर्णांकel_mocs_init(काष्ठा पूर्णांकel_gt *gt);
व्योम पूर्णांकel_mocs_init_engine(काष्ठा पूर्णांकel_engine_cs *engine);

#पूर्ण_अगर
