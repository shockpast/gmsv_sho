# gmsv_sho
idk, it removes `do_constraint_system: Couldn't invert rot matrix!` message, maybe it works, idkkkkkkkkkkkkk

## hooks
### `sho:SetAbsOrigin`
it has 2 arguments, `string class, number idx`, it's id of entity and the classname of entity that would spam message "Ignoring Unreasonable Position!", you can hook it and then just remove it, so it won't garbage your server, or do whatever with it *(beware, players can also trigger it)*
