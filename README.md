# gmsv_sho

A Garry's Mod server module that provides physics environment control and message filtering capabilities.

## Features

- Physics environment control through `iphysenv` interface (only main)
- Filtering of common spam messages and warnings
- Hooks for handling unreasonable entity positions

## Installation

1. Download the latest release for your platform
2. Place the binary in your server's `garrysmod/lua/bin` directory
3. Add `require("sho")` to your server's startup scripts

## Usage

### Physics Environment

```lua
-- Control physics simulation
iphysenv.ShouldSimulate(true) -- Enable/disable physics simulation
iphysenv.Status() -- Get current simulation status

-- Modify gravity
iphysenv.SetGravity(Vector(0, 0, -600))
local gravity = iphysenv.GetGravity()
```

### Position Monitoring

The module provides hooks for detecting and handling invalid entity positions:

```lua
hook.Add("sho:SetAbsOrigin", "handle_bad_pos", function(entityIndex)
  local ent = Entity(entityIndex)
  if not IsValid(ent) then return end

  -- Handle the invalid position...
end)
```

## Building

Requires:
- [garrysmod_common](https://github.com/danielga/garrysmod_common)
- A compatible C++ compiler
- premake5

1. Clone:
```bash
git clone https://github.com/user/gmsv_sho.git
```

2. Run premake:
```bash
premake5 vs2019 # Or your preferred generator
```

3. Build using generated project files