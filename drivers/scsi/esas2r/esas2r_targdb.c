<शैली गुरु>
/*
 *  linux/drivers/scsi/esas2r/esas2r_targdb.c
 *      For use with ATTO ExpressSAS R6xx SAS/SATA RAID controllers
 *
 *  Copyright (c) 2001-2013 ATTO Technology, Inc.
 *  (mailto:linuxdrivers@attotech.com)
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * NO WARRANTY
 * THE PROGRAM IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT
 * LIMITATION, ANY WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT,
 * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE. Each Recipient is
 * solely responsible क्रम determining the appropriateness of using and
 * distributing the Program and assumes all risks associated with its
 * exercise of rights under this Agreement, including but not limited to
 * the risks and costs of program errors, damage to or loss of data,
 * programs or equipment, and unavailability or पूर्णांकerruption of operations.
 *
 * DISCLAIMER OF LIABILITY
 * NEITHER RECIPIENT NOR ANY CONTRIBUTORS SHALL HAVE ANY LIABILITY FOR ANY
 * सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING WITHOUT LIMITATION LOST PROFITS), HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
 * TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OR DISTRIBUTION OF THE PROGRAM OR THE EXERCISE OF ANY RIGHTS GRANTED
 * HEREUNDER, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGES
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fअगरth Floor, Boston, MA  02110-1301,
 * USA.
 */

#समावेश "esas2r.h"

व्योम esas2r_targ_db_initialize(काष्ठा esas2r_adapter *a)
अणु
	काष्ठा esas2r_target *t;

	क्रम (t = a->targetdb; t < a->targetdb_end; t++) अणु
		स_रखो(t, 0, माप(काष्ठा esas2r_target));

		t->target_state = TS_NOT_PRESENT;
		t->buffered_target_state = TS_NOT_PRESENT;
		t->new_target_state = TS_INVALID;
	पूर्ण
पूर्ण

व्योम esas2r_targ_db_हटाओ_all(काष्ठा esas2r_adapter *a, bool notअगरy)
अणु
	काष्ठा esas2r_target *t;
	अचिन्हित दीर्घ flags;

	क्रम (t = a->targetdb; t < a->targetdb_end; t++) अणु
		अगर (t->target_state != TS_PRESENT)
			जारी;

		spin_lock_irqsave(&a->mem_lock, flags);
		esas2r_targ_db_हटाओ(a, t);
		spin_unlock_irqrestore(&a->mem_lock, flags);

		अगर (notअगरy) अणु
			esas2r_trace("remove id:%d", esas2r_targ_get_id(t,
									a));
			esas2r_target_state_changed(a, esas2r_targ_get_id(t,
									  a),
						    TS_NOT_PRESENT);
		पूर्ण
	पूर्ण
पूर्ण

व्योम esas2r_targ_db_report_changes(काष्ठा esas2r_adapter *a)
अणु
	काष्ठा esas2r_target *t;
	अचिन्हित दीर्घ flags;

	esas2r_trace_enter();

	अगर (test_bit(AF_DISC_PENDING, &a->flags)) अणु
		esas2r_trace_निकास();
		वापस;
	पूर्ण

	क्रम (t = a->targetdb; t < a->targetdb_end; t++) अणु
		u8 state = TS_INVALID;

		spin_lock_irqsave(&a->mem_lock, flags);
		अगर (t->buffered_target_state != t->target_state)
			state = t->buffered_target_state = t->target_state;

		spin_unlock_irqrestore(&a->mem_lock, flags);
		अगर (state != TS_INVALID) अणु
			esas2r_trace("targ_db_report_changes:%d",
				     esas2r_targ_get_id(
					     t,
					     a));
			esas2r_trace("state:%d", state);

			esas2r_target_state_changed(a,
						    esas2r_targ_get_id(t,
								       a),
						    state);
		पूर्ण
	पूर्ण

	esas2r_trace_निकास();
पूर्ण

काष्ठा esas2r_target *esas2r_targ_db_add_raid(काष्ठा esas2r_adapter *a,
					      काष्ठा esas2r_disc_context *
					      dc)
अणु
	काष्ठा esas2r_target *t;

	esas2r_trace_enter();

	अगर (dc->curr_virt_id >= ESAS2R_MAX_TARGETS) अणु
		esas2r_bugon();
		esas2r_trace_निकास();
		वापस शून्य;
	पूर्ण

	t = a->targetdb + dc->curr_virt_id;

	अगर (t->target_state == TS_PRESENT) अणु
		esas2r_trace_निकास();
		वापस शून्य;
	पूर्ण

	esas2r_hdebug("add RAID %s, T:%d", dc->raid_grp_name,
		      esas2r_targ_get_id(
			      t,
			      a));

	अगर (dc->पूर्णांकerleave == 0
	    || dc->block_size  == 0) अणु
		/* these are invalid values, करोn't create the target entry. */

		esas2r_hdebug("invalid RAID group dimensions");

		esas2r_trace_निकास();

		वापस शून्य;
	पूर्ण

	t->block_size = dc->block_size;
	t->पूर्णांकer_byte = dc->पूर्णांकerleave;
	t->पूर्णांकer_block = dc->पूर्णांकerleave / dc->block_size;
	t->virt_targ_id = dc->curr_virt_id;
	t->phys_targ_id = ESAS2R_TARG_ID_INV;

	t->flags &= ~TF_PASS_THRU;
	t->flags |= TF_USED;

	t->identअगरier_len = 0;

	t->target_state = TS_PRESENT;

	वापस t;
पूर्ण

काष्ठा esas2r_target *esas2r_targ_db_add_pthru(काष्ठा esas2r_adapter *a,
					       काष्ठा esas2r_disc_context *dc,
					       u8 *ident,
					       u8 ident_len)
अणु
	काष्ठा esas2r_target *t;

	esas2r_trace_enter();

	अगर (dc->curr_virt_id >= ESAS2R_MAX_TARGETS) अणु
		esas2r_bugon();
		esas2r_trace_निकास();
		वापस शून्य;
	पूर्ण

	/* see अगर we found this device beक्रमe. */

	t = esas2r_targ_db_find_by_ident(a, ident, ident_len);

	अगर (t == शून्य) अणु
		t = a->targetdb + dc->curr_virt_id;

		अगर (ident_len > माप(t->identअगरier)
		    || t->target_state == TS_PRESENT) अणु
			esas2r_trace_निकास();
			वापस शून्य;
		पूर्ण
	पूर्ण

	esas2r_hdebug("add PT; T:%d, V:%d, P:%d", esas2r_targ_get_id(t, a),
		      dc->curr_virt_id,
		      dc->curr_phys_id);

	t->block_size = 0;
	t->पूर्णांकer_byte = 0;
	t->पूर्णांकer_block = 0;
	t->virt_targ_id = dc->curr_virt_id;
	t->phys_targ_id = dc->curr_phys_id;
	t->identअगरier_len = ident_len;

	स_नकल(t->identअगरier, ident, ident_len);

	t->flags |= TF_PASS_THRU | TF_USED;

	t->target_state = TS_PRESENT;

	वापस t;
पूर्ण

व्योम esas2r_targ_db_हटाओ(काष्ठा esas2r_adapter *a, काष्ठा esas2r_target *t)
अणु
	esas2r_trace_enter();

	t->target_state = TS_NOT_PRESENT;

	esas2r_trace("remove id:%d", esas2r_targ_get_id(t, a));

	esas2r_trace_निकास();
पूर्ण

काष्ठा esas2r_target *esas2r_targ_db_find_by_sas_addr(काष्ठा esas2r_adapter *a,
						      u64 *sas_addr)
अणु
	काष्ठा esas2r_target *t;

	क्रम (t = a->targetdb; t < a->targetdb_end; t++)
		अगर (t->sas_addr == *sas_addr)
			वापस t;

	वापस शून्य;
पूर्ण

काष्ठा esas2r_target *esas2r_targ_db_find_by_ident(काष्ठा esas2r_adapter *a,
						   व्योम *identअगरier,
						   u8 ident_len)
अणु
	काष्ठा esas2r_target *t;

	क्रम (t = a->targetdb; t < a->targetdb_end; t++) अणु
		अगर (ident_len == t->identअगरier_len
		    && स_भेद(&t->identअगरier[0], identअगरier,
			      ident_len) == 0)
			वापस t;
	पूर्ण

	वापस शून्य;
पूर्ण

u16 esas2r_targ_db_find_next_present(काष्ठा esas2r_adapter *a, u16 target_id)
अणु
	u16 id = target_id + 1;

	जबतक (id < ESAS2R_MAX_TARGETS) अणु
		काष्ठा esas2r_target *t = a->targetdb + id;

		अगर (t->target_state == TS_PRESENT)
			अवरोध;

		id++;
	पूर्ण

	वापस id;
पूर्ण

काष्ठा esas2r_target *esas2r_targ_db_find_by_virt_id(काष्ठा esas2r_adapter *a,
						     u16 virt_id)
अणु
	काष्ठा esas2r_target *t;

	क्रम (t = a->targetdb; t < a->targetdb_end; t++) अणु
		अगर (t->target_state != TS_PRESENT)
			जारी;

		अगर (t->virt_targ_id == virt_id)
			वापस t;
	पूर्ण

	वापस शून्य;
पूर्ण

u16 esas2r_targ_db_get_tgt_cnt(काष्ठा esas2r_adapter *a)
अणु
	u16 devcnt = 0;
	काष्ठा esas2r_target *t;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&a->mem_lock, flags);
	क्रम (t = a->targetdb; t < a->targetdb_end; t++)
		अगर (t->target_state == TS_PRESENT)
			devcnt++;

	spin_unlock_irqrestore(&a->mem_lock, flags);

	वापस devcnt;
पूर्ण
