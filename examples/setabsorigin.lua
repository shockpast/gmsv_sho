hook.Add("sho:SetAbsOrigin", "t", function(class, idx)
  local ent = Entity(idx)
  if not IsValid(ent) then return end
  if ent:IsPlayer() then
    print(ent, " was in wrong position.")
    print(ent:SteamID())

    ent:SetPos(Vector(0, 0, 0))
    return -- just don't delete your player, pretty please :)
  end

  print(ent, " was removed")
  print(ent:GetPos())

  ent:Remove()
end)
