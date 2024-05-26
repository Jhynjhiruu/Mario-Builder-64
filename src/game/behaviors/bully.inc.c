// bully.inc.c

static struct ObjectHitbox sSmallBullyHitbox = {
    /* interactType:      */ INTERACT_BULLY,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 1,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 73,
    /* height:            */ 123,
    /* hurtboxRadius:     */ 63,
    /* hurtboxHeight:     */ 113,
};

static struct ObjectHitbox sBigBullyHitbox = {
    /* interactType:      */ INTERACT_BULLY,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 1,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 115,
    /* height:            */ 235,
    /* hurtboxRadius:     */ 105,
    /* hurtboxHeight:     */ 225,
};

void bhv_small_bully_init(void) {
    o->oQuicksandDepthToDie = 55;

    cur_obj_init_animation(0);
    o->oBehParams2ndByte = BULLY_BP_SIZE_SMALL;
    o->oGravity = 4.0f;
    o->oFriction = 0.91f;
    o->oBuoyancy = 1.3f;
    o->oWallHitboxRadius = 50.f;

    obj_set_hitbox(o, &sSmallBullyHitbox);
}

void bhv_big_bully_init(void) {
    o->oQuicksandDepthToDie = 150;
    cur_obj_init_animation(0);
    o->oBehParams2ndByte = BULLY_BP_SIZE_BIG;
    o->oGravity = 5.0f;
    o->oFriction = 0.93f;
    o->oBuoyancy = 1.3f;
    o->oWallHitboxRadius = 100.f;

    obj_set_hitbox(o, &sBigBullyHitbox);
}

void bully_check_mario_collision(void) {
    if (o->oAction != OBJ_ACT_LAVA_DEATH && o->oAction != OBJ_ACT_DEATH_PLANE_DEATH && o->oInteractStatus & INT_STATUS_INTERACTED) {
        if (o->oBehParams2ndByte == BULLY_BP_SIZE_SMALL) {
            cur_obj_play_sound_2(SOUND_OBJ2_SMALL_BULLY_ATTACKED);
        } else {
            cur_obj_play_sound_2(SOUND_OBJ2_LARGE_BULLY_ATTACKED);
        }

        o->oInteractStatus &= ~INT_STATUS_INTERACTED;
        o->oAction = BULLY_ACT_KNOCKBACK;
        o->oBullyKBTimerAndMinionKOCounter = 0;
        o->oFlags &= ~OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW;
        cur_obj_init_animation(3);
    }
}

void bully_act_chase_mario(void) {
    if (o->oTimer < 10) {
        o->oForwardVel = 3.0f;
        obj_turn_toward_object(o, gMarioObject, O_MOVE_ANGLE_YAW_INDEX, 0x1000);
    } else if (o->oBehParams2ndByte == BULLY_BP_SIZE_SMALL) {
        o->oForwardVel = 20.0f;
        if (o->oTimer > 30) {
            o->oTimer = 0;
        }
    } else {
        o->oForwardVel = 30.0f;
        if (o->oTimer > 35) {
            o->oTimer = 0;
        }
    }

    if (o->oDistanceToMario > 1000.f) {
        o->oAction = BULLY_ACT_PATROL;
        cur_obj_init_animation(0);
    }
}

void bully_act_knockback(void) {
    if (o->oForwardVel < 10.0f && (s32) o->oVelY == 0) {
        o->oForwardVel = 1.0f;
        o->oBullyKBTimerAndMinionKOCounter++;
        o->oFlags |= OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW;
        o->oMoveAngleYaw = o->oFaceAngleYaw;
        obj_turn_toward_object(o, gMarioObject, O_MOVE_ANGLE_YAW_INDEX, 1280);
    } else {
        o->header.gfx.animInfo.animFrame = 0;
    }

    if (o->oBullyKBTimerAndMinionKOCounter == 18) {
        o->oAction = BULLY_ACT_CHASE_MARIO;
        o->oBullyKBTimerAndMinionKOCounter = 0;
        cur_obj_init_animation(1);
    }
}

void bully_act_back_up(void) {
    if (o->oTimer == 0) {
        o->oFlags &= ~OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW;
        o->oMoveAngleYaw += 0x8000;
    }

    o->oForwardVel = 5.0f;

    //! bully_backup_check() happens after this function, and has the potential to reset
    //  the bully's action to BULLY_ACT_BACK_UP. Because the back up action is only
    //  set to end when the timer EQUALS 15, if this happens on that frame, the bully
    //  will be stuck in BULLY_ACT_BACK_UP forever until Mario hits it or its death
    //  conditions are activated. However because its angle is set to its facing angle,
    //  it will walk forward instead of backing up.

    if (o->oTimer >= 15) {
        o->oMoveAngleYaw = o->oFaceAngleYaw;
        o->oFlags |= OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW;
        o->oAction = BULLY_ACT_PATROL;
    }
}

void bully_backup_check(s16 collisionFlags) {
    if (!(collisionFlags & OBJ_COL_FLAG_NO_Y_VEL) && o->oAction != BULLY_ACT_KNOCKBACK && !o->oBullyInMidair) {
        o->oPosX = o->oBullyPrevX;
        o->oPosZ = o->oBullyPrevZ;
        o->oAction = BULLY_ACT_BACK_UP;
    }
}

void bully_play_stomping_sound(void) {
    s16 animFrame = o->header.gfx.animInfo.animFrame;

    switch (o->oAction) {
        case BULLY_ACT_PATROL:
            if (animFrame == 0 || animFrame == 12) {
                if (o->oBehParams2ndByte == BULLY_BP_SIZE_SMALL) {
                    cur_obj_play_sound_2(SOUND_OBJ_BULLY_WALK_SMALL);
                } else {
                    cur_obj_play_sound_2(SOUND_OBJ_BULLY_WALK_LARGE);
                }
            }
            break;

        case BULLY_ACT_CHASE_MARIO:
        case BULLY_ACT_BACK_UP:
            if (animFrame == 0 || animFrame == 5) {
                if (o->oBehParams2ndByte == BULLY_BP_SIZE_SMALL) {
                    cur_obj_play_sound_2(SOUND_OBJ_BULLY_WALK_SMALL);
                } else {
                    cur_obj_play_sound_2(SOUND_OBJ_BULLY_WALK_LARGE);
                }
            }
            break;
    }
}

void bully_step(void) {
    s16 collisionFlags = object_step();
    cur_obj_set_home_if_safe();

    bully_backup_check(collisionFlags);
    bully_play_stomping_sound();
    obj_check_floor_death(collisionFlags, sObjFloor);

    if (o->oBullySubtype & BULLY_STYPE_CHILL) {
        if (o->oPosY < 1030.0f) {
            o->oAction = OBJ_ACT_LAVA_DEATH;
        }
    }
}

void bully_spawn_coin(void) {
    struct Object *coin = spawn_object(o, MODEL_YELLOW_COIN, bhvMovingYellowCoin);

    cur_obj_play_sound_2(SOUND_GENERAL_COIN_SPURT);

    coin->oForwardVel = 10.0f;
    coin->oVelY = 100.0f;
    coin->oPosY = o->oPosY + 310.0f;
    coin->oMoveAngleYaw = o->oAngleToMario + (random_float() * 1024.0f);
}

// offset home a little bit so stuff doesnt spawn on the very edge
void bully_adjust_imbued_drop_location(void) {
    if (o->oImbue == IMBUE_STAR) return;
    s16 angle = atan2s(o->oHomeZ - o->oPosZ, o->oHomeX - o->oPosX);
    o->oHomeX += 70.0f * sins(angle);
    o->oHomeZ += 70.0f * coss(angle);
    f32 newY = find_floor_height(o->oHomeX, o->oHomeY + 100.f, o->oHomeZ);
    if (newY > o->oHomeY - 100.f) {
        o->oHomeY = newY;
    }
}

void bully_act_level_death(void) {
    if (obj_lava_death() == TRUE) {
        if (o->oBehParams2ndByte == BULLY_BP_SIZE_SMALL) {
            if (o->oBullySubtype == BULLY_STYPE_MINION) {
                o->parentObj->oBullyKBTimerAndMinionKOCounter++;
            }
            bully_spawn_coin();
        } else {
            spawn_mist_particles();
            bully_adjust_imbued_drop_location();
            cur_obj_drop_imbued_object(400);

            /*
            if (o->oBullySubtype == BULLY_STYPE_CHILL) {
                spawn_default_star(130.0f, 1600.0f, -4335.0f);
            } else {
                spawn_default_star(0, 950.0f, -6800.0f);
                spawn_object_abs_with_rot(o, 0, MODEL_NONE, bhvLllTumblingBridge,
                                          0, 154, -5631, 0, 0, 0);
            }*/
        }
    }
}

void bhv_bully_loop(void) {
    vec3f_copy(&o->oBullyPrevVec, &o->oPosVec);
    o->oBullyInMidair = (o->oPosY > o->oFloorHeight + 4.f);

    if (o->oAction < OBJ_ACT_LAVA_DEATH) bully_check_mario_collision();
    switch (o->oAction) {
        case BULLY_ACT_PATROL:
            o->oForwardVel = 5.0f;
            o->oMoveAngleYaw += 320;

            if (o->oDistanceToMario < 800.f) {
                o->oAction = BULLY_ACT_CHASE_MARIO;
                cur_obj_init_animation(1);
            }

            bully_step();
            break;

        case BULLY_ACT_CHASE_MARIO:
            bully_act_chase_mario();
            bully_step();
            break;

        case BULLY_ACT_KNOCKBACK:
            bully_act_knockback();
            bully_step();
            break;

        case BULLY_ACT_BACK_UP:
            bully_act_back_up();
            bully_step();
            break;

        case OBJ_ACT_LAVA_DEATH:
            bully_act_level_death();
            break;

        case OBJ_ACT_DEATH_PLANE_DEATH:
            bully_adjust_imbued_drop_location();
            cur_obj_drop_imbued_object(400);
            o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
            break;
    }
}

void big_bully_spawn_minion(s32 x, s32 y, s32 z, s16 yaw) {
    struct Object *bully =
        spawn_object_abs_with_rot(o, 0, MODEL_BULLY, bhvSmallBully, x, y, z, 0, yaw, 0);
    bully->oBullySubtype = BULLY_STYPE_MINION;
    bully->oBehParams2ndByte = BULLY_BP_SIZE_SMALL;
}

void bhv_big_bully_with_minions_init(void) {
    big_bully_spawn_minion(4454, 307, -5426, 0);
    big_bully_spawn_minion(3840, 307, -6041, 0);
    big_bully_spawn_minion(3226, 307, -5426, 0);

    o->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;

    cur_obj_become_intangible();

    o->oAction = BULLY_ACT_INACTIVE;
}

void big_bully_spawn_star(void) {
    if (obj_lava_death() == TRUE) {
        spawn_mist_particles();
        spawn_default_star(3700.0f, 600.0f, -5500.0f);
    }
}

void bhv_big_bully_with_minions_loop(void) {
    s16 collisionFlags = 0;
    vec3f_copy(&o->oBullyPrevVec, &o->oPosVec);

    bully_check_mario_collision();

    switch (o->oAction) {
        case BULLY_ACT_PATROL:
            o->oForwardVel = 5.0f;
            o->oMoveAngleYaw += 320;

            if (o->oDistanceToMario < 1000.f) {
                o->oAction = BULLY_ACT_CHASE_MARIO;
                cur_obj_init_animation(1);
            }

            bully_step();
            break;

        case BULLY_ACT_CHASE_MARIO:
            bully_act_chase_mario();
            bully_step();
            break;

        case BULLY_ACT_KNOCKBACK:
            bully_act_knockback();
            bully_step();
            break;

        case BULLY_ACT_BACK_UP:
            bully_act_back_up();
            bully_step();
            break;

        case BULLY_ACT_INACTIVE:
            //! The Big Bully that spawns from killing its 3 minions uses the knockback timer
            //  for counting the number of dead minions. This means that when it activates,
            //  the knockback timer is at 3 instead of 0. So the bully knockback time will
            //  be reduced by 3 frames (16.67%) on the first hit.
            if (o->oBullyKBTimerAndMinionKOCounter == 3) {
                play_puzzle_jingle();

                if (o->oTimer > 90) {
                    o->oAction = BULLY_ACT_ACTIVATE_AND_FALL;
                }
            }
            break;

        case BULLY_ACT_ACTIVATE_AND_FALL:
            collisionFlags = object_step();
            if ((collisionFlags & OBJ_COL_FLAGS_LANDED) == OBJ_COL_FLAGS_LANDED) {
                o->oAction = BULLY_ACT_PATROL;
            }

            if (collisionFlags == OBJ_COL_FLAG_GROUNDED) {
                cur_obj_play_sound_2(SOUND_OBJ_THWOMP);
                set_camera_shake_from_point(SHAKE_POS_SMALL, o->oPosX, o->oPosY, o->oPosZ);
                spawn_mist_particles();
            }

            o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
            cur_obj_become_tangible();
            break;

        case OBJ_ACT_LAVA_DEATH:
            big_bully_spawn_star();
            break;

        case OBJ_ACT_DEATH_PLANE_DEATH:
            bully_adjust_imbued_drop_location();
            cur_obj_drop_imbued_object(400);
            o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
            break;
    }
}